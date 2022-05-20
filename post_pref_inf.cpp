#include<iostream>
#include<vector>
#include<string>
#include<algorithm>


using namespace std;
string s;

struct Node {
    string c;
    int prior;
    Node* left = nullptr;
    Node* right = nullptr;
    Node (string c1, int prior1, Node* x, Node* y) {
        c = c1;
        prior = prior1;
        left = x;
        right = y;
    }
};

void print_inf (Node* p) {
    if (p == nullptr) {
        return;
    }
    if (!p->left) {
        cout << p->c;
        return;
    }
    if ((p->left->prior == 1) && (p->prior == 2)) {
        cout << "(";
        print_inf(p->left);
        cout << ") ";
    } else {
        print_inf(p->left);
    }
    cout << p->c << " ";
    if ((p->right->prior == 1) && (p->prior == 2)) {
        cout << "(";
        print_inf(p->right);
        cout << ") ";
    } else {
        print_inf(p->right);
    }
}
void print_post(Node* p) {
    if (p == nullptr) {
        return;
    }
    print_post(p->left);
    print_post(p->right);
    cout << p->c << " ";
}

void print_pref(Node* p) {
    if (p == nullptr) {
        return;
    }
    cout << p->c << " ";
    print_pref(p->left);
    print_pref(p->right);
}

Node* inf_to_tree(string t) {
    string t1 = t;
    if (t[0] == '(') {
        int cnt = 1;
        bool x  = false;
        for (int i = 1; i < t.size(); i++) {
            if (t[i] == '(') {
                cnt++;
            } else if (t[i] == ')'){
                cnt--;
                if (i != t.size() - 1) {
                    x = true;
                }
            }
        }
        if (!x) {
            t = "";
            for (int i = 1; i < t1.size() - 1; i++) {
                t += t1[i];
            }
        }
    }
    int cnt = 0;
    int cnt_min = 1e9;
    int ind = -1;
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == '(') {
            cnt++;
        }
        if (t[i] == ')') {
            cnt--;
        }
        if ((t[i] == '+') || (t[i] == '-') || (t[i] =='*') || (t[i] == '/')) {
            if (cnt < cnt_min) {
                cnt_min = cnt;
                ind = i;
            }
        }
    }
    if (ind == -1) {
        return new Node (t, 0, nullptr, nullptr);
    }
    string s1, s2;
    s1 = s2 = "";
    for (int i = 0; i < (t[ind - 1] == ' ' ? ind - 1 : ind); i++) {
        s1 += t[i];
    }
    for (int i = (t[ind + 1] == ' ' ? ind + 2 : ind + 1); i < t.size(); i++) {
        s2 += t[i];
    }
    string col = "";
    col += t[ind];
    if ((t[ind] == '+') || (t[ind] == '-')) {
        return new Node (col, 1, inf_to_tree(s1), inf_to_tree(s2));
    }
    return new Node (col, 2, inf_to_tree(s1), inf_to_tree(s2));
}

Node* pref_to_tree(string t) {
    if (t == "")
        return nullptr;
    if ((t[0] != '-') && (t[0] != '+') && (t[0] != '*') && (t[0] != '/')) {
        return new Node(t, 0, nullptr, nullptr);
    }
    int cnt = 1;
    int ind = -1;
    for (int i = 2; i < t.size(); i++) {
        if ((t[i] == '+') || (t[i] == '-') || (t[i] == '*') || (t[i] == '/')) {
            cnt++;
        } else {
            if (t[i] != ' ') {
                while ((i < t.size()) && (t[i] != ' ')) {
                    i++;
                }
                cnt--;
                if (cnt == 0) {
                    ind = i;
                    break;
                }
            }
        }
    }
    string s13 = "";
    for (int i = 2; i < ind; i++) {
        s13 += t[i];
    }
    string s2 = "";
    for (int i = ind + 1; i < t.size(); i++) {
        s2 += t[i];
    }
    string first1 = "";
    first1 += t[0];
    if ((t[0] == '+') || (t[0] == '-')) {
        return new Node (first1, 1, pref_to_tree(s13), pref_to_tree(s2));
    }
    return new Node (first1, 2, pref_to_tree(s13), pref_to_tree(s2));
}

Node* post_to_tree(string t) {
    if (t == "")
        return nullptr;
    if ((t[t.size() - 1] != '-') && (t[t.size() - 1] != '+') && (t[t.size() - 1] != '*') && (t[t.size() - 1] != '/')) {
        return new Node(t, 0, nullptr, nullptr);
    }
    int cnt = 1;
    int ind = -1;
    for (int i = 0; i < t.size(); i++) {
        if ((t[i] == '+') || (t[i] == '-') || (t[i] == '*') || (t[i] == '/')) {
            cnt++;
            if ((cnt == 0) && (i != t.size() - 1)) {
                ind = i + 1;
            }
        } else {
            if (t[i] != ' ') {
                while ((i < t.size()) && (t[i] != ' ')) {
                    i++;
                }
                cnt--;

                if ((cnt == 0) && (i < t.size() - 1)) {
                    ind = i;
                }
            }
        }
    }
    string s13 = "";
    for (int i = 0; i < ind; i++) {
        s13 += t[i];
    }
    string s2 = "";
    for (int i = ind + 1; i < t.size() - 2; i++) {
        s2 += t[i];
    }
    string first1 = "";
    first1 += t[t.size() - 1];
    if ((t[t.size() - 1] == '+') || (t[t.size() - 1] == '-')) {
        return new Node (first1, 1, post_to_tree(s13), post_to_tree(s2));
    }
    return new Node (first1, 2, post_to_tree(s13), post_to_tree(s2));
}

void solve_pref() {
    Node* t = pref_to_tree(s);
    cout << "infix: ";
    print_inf(t);
    cout << endl;
    cout << "postfix: ";
    print_post(t);
}

void solve_inf() {
    Node* t = inf_to_tree(s);
    cout << "prefix: ";
    print_pref(t);
    cout << "\npostfix: ";
    print_post(t);

}

void solve_post() {
    Node* t = post_to_tree(s);
    cout << "infix: ";
    print_inf(t);
    cout << endl;
    cout << "prefix : ";
    print_pref(t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s1;
    getline(cin, s1);
    getline(cin, s);
    if (s1 == "prefix")
        solve_pref();
    if (s1 == "infix")
        solve_inf();
    if (s1 == "postfix")
        solve_post();
    return 0;
}
