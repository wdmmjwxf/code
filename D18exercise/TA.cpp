#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int ans, v[105], dp[105][35][35][16], pw[105][35];

int C[35][35];
inline void init(int n) {
	for (int i = 0; i <= n; i++) C[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

inline int popcnt(int n) {
	int res = 0;
	while (n) res += n & 1, n >>= 1;
	return res;
}

int main() {
	init(30);
	int n, m, K;
	cin>>n>>m>>K;
	for (int i = 0; i <= m; i++) {
		cin>>v[i];
		pw[i][0] = 1;
		for (int j = 1; j <= n; j++) pw[i][j] = pw[i][j - 1] * v[i] % mod;
	}
	dp[0][0][0][0] = 1;
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= K; k++)
				for (int p = 0; p <= n >> 1; p++)
					for (int t = 0; t <= n - j; t++) dp[i + 1][j + t][k + (t + p & 1)][t + p >> 1] = (dp[i + 1][j + t][k + (t + p & 1)][t + p >> 1] + dp[i][j][k][p] * pw[i][t] % mod * C[n - j][t] % mod) % mod;
	for (int k = 0; k <= K; k++)
		for (int p = 0; p <= n >> 1; p++)
			if (k + popcnt(p) <= K) ans = (ans + dp[m + 1][n][k][p]) % mod;
	cout<<ans;
	return 0;
}