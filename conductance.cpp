#include <bits/stdc++.h>

using namespace std;
#define forl(i, a, n) for (int i = a; i < n; i++)
#define fore(i, a, n) for (int i = a; i <= n; i++)
#define rev(i, n) for (int i = n - 1; i >= 0; i--)
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define ll long long
#define lli long long int
#define mem(a, k) memset(a, k, sizeof(a))
#define sp << " " <<
#define CASE(t, k) cout << "Case #" << (t) << ": " << (k) << endl
#define LIMIT 1000000
const int maxn = 200000 + 10;
const int mod = 1000000007;

double parallel(vector<string>);

vector<string> split(const string &s)
{
	vector<string> v;
	int x = 2;
	stack<int> st;
	forl(i, 2, s.length() - 1)
	{
		if (s[i] == '(')
			st.push(1);
		else if (s[i] == ')')
			st.pop();
		else if (s[i] == ',' && st.empty())
		{
			v.pb(s.substr(x, i - x));
			x = i + 1;
		}
	}
	v.pb(s.substr(x, s.length() - 1 - x));
	return v;
}

double series(vector<string> pipes)
{
	if (pipes.empty())
		return 0;
	double ans = 0;
	for (string s : pipes)
	{
		if (int('9' - s[0]) <= 9 && int('9' - s[0]) >= 0)
			ans += 1 / stod(s);
		else if (s[0] == 'P' || s[0] == 'p')
			ans += 1 / parallel(split(s));
		else if (s[0] == 'S' || s[0] == 's')
			ans += 1 / series(split(s));
	}
	return 1 / ans;
}

double parallel(vector<string> pipes)
{
	if (pipes.empty())
		return 0;
	double ans = 0;
	for (string s : pipes)
	{
		if (int('9' - s[0]) <= 9 && int('9' - s[0]) >= 0)
			ans += stod(s);
		else if (s[0] == 'P' || s[0] == 'p')
			ans += parallel(split(s));
		else if (s[0] == 'S' || s[0] == 's')
			ans += series(split(s));
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	//Instructions for input
	cout << "Enter sequence of pipes with their conductances(in L/s) in the following format" << endl;
	cout << "(S-Series, P-Parallel): S(1.2,P(0.5,1,2),S(3.1,4))" << endl;
	cout << "1. Remember to mention series or parallel before opening brackets." << endl;
	cout << "2. Make sure brackets and commas are correctly placed." << endl;
	cout << "3. Decimals <1 should have a 0 before decimal point." << endl;
	cout << "4. Avoid any kind of spaces.\nInput:" << endl;
	string s;
start:
	cin >> s;

	// Validating input
	if (s.find(",.") != string::npos || s.find("(.") != string::npos)
	{
		cout << "Warning! Enter 0 before decimal point.\nInput:" << endl;
		goto start;
	}
	stack<int> st;
	forl(i, 0, s.length())
	{
		if (s[i] == '(')
		{
			st.push(1);
			if (s[i - 1] != 'S' && s[i - 1] != 'P' && s[i - 1] != 's' && s[i - 1] != 'p')
			{
				cout << "Please mention series or parallel before bracket.\nInput:" << endl;
				goto start;
			}
		}
		else if (s[i] == ')' && !st.empty())
			st.pop();
		else if (s[i] == ')' && st.empty())
		{
			cout << "Warning! Recheck formatting.\nInput:" << endl;
			goto start;
		}
	}
	if (!st.empty())
	{
		cout << "Warning! Recheck fromatting.\nInput:" << endl;
		goto start;
	}

	//Retrieving answer from string
	double ans = 0;
	if (s[0] == 'S' || s[0] == 's')
		ans = series(split(s));
	else if (s[0] == 'P' || s[0] == 'p')
		ans = parallel(split(s));

	//Outputs calculated answer
	cout << "Total Conductance of Pipes: " << ans << " L/s" << endl;
	return 0;
}