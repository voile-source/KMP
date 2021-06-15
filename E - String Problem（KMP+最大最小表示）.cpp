/**对于一个长n的字符串s，可以进行左移操作，即将前1位移至串尾，进行n次左移操作，可以得到n个与原串循环同构的字符串，现在要求出这字符串s中最小表示的位置和最大表示的位置，以及在n个循环同构的字符串中分别出现了多少次。
例如：字符串"SKYLONG"
SKYLONG 1
KYLONGS 2
YLONGSK 3
LONGSKY 4
ONGSKYL 5
NGSKYLO 6
GSKYLON 7
最小表示是GSKYLON，最大表示是YLONGSK，都只出现了一次。
Input
每一行包含一个字符串s(|s| <= 1000000)。（用EOF作为结束输入标志）
Output
每一行对应一个字符串的输出，每行包含四个整数并用空格隔开，第一个整数代表最小表示的位置，第二个整数代表最小表示出现的次数，第三个整数代表最大表示的位置，第四个整数代表最大表示出现的次数。
Sample Input
abcder
aaaaaa
ababab
Sample Output
1 1 6 1
1 6 1 6
1 3 2 3
Sponsor

解题思路：最小最大化+kmp next数组，最大最小化的表示位置可以用最大最小化的表示方法来求，出现次数就是循环节的数量，可以用kmp的next数组求；

**/

#include<iostream>
#include<string>
#include<cstring>
using namespace std;
const int max_n=1e6+10;

string s;
int nex[max_n];

void getnext()
{
	for(int i=2,j=0;i<s.size();i++){
		while(j&&s[i]!=s[j+1])j=nex[j];
		if(s[i]==s[j+1])j++;
		nex[i]=j;	
	}
}

int get(int flag)
{
	int i=0,j=1,k=0;
	int n=s.size();
	while(i<n&&j<n&&k<n){
		int t=s[(j+k)%n]-s[(i+k)%n];
		if(t==0)k++;
		else{
			if(flag){
				if(t>0)j=j+k+1;
				else i=i+k+1;
			} else {
				if(t>0)i=i+k+1;
				else j=j+k+1;
			}
			if(i==j)j++;
		    k=0;
		}
	}
	return min(i,j)+1;
}

int main()
{	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin>>s){
		int mi=get(1);
		int ma=get(0);
		s=' '+s;
		getnext();
		int n=s.size()-1;
		int k=n-nex[n];
		int ans=n%k?1:n/k;
		cout<<mi<<' '<<ans<<' '<<ma<<' '<<ans<<endl;
	}
}
