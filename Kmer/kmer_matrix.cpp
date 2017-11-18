#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;


const int K = 25;


char st[1000];
int b[1000];
long long po[30];


unordered_map<long long, long long> maps;
//map<string, int> maps;



int main(int argc,char *argv[]){
	int i,j,k;
	DIR *dp;
	struct dirent *dirp;
	int n=0;
	if (argc!=2){
		printf("a single argument is required\n");
		return 0;
	}
	if((dp=opendir(argv[1]))==NULL)
		printf("can't open %s",argv[1]);

	memset(b,0,sizeof(b));
	b['A']=1;
	b['C']=2;
	b['G']=3;
	b['T']=4;
	b['N']=5;
	maps.clear();
	po[0]=1;
	for (int i=1;i<30;i++) {
		po[i]=po[i-1]*4;
	}
	int maxs=0;
	
	while (((dirp=readdir(dp))!=NULL)){
		string s;
		s = dirp->d_name;
		if (s[0]<='6' && s[0]>='1') {
			long long ttt = s[0] -'0' - 1;
			n++;
			FILE * pFILE;
			pFILE = fopen(s.c_str(),"r");
						
			fscanf(pFILE, "%d",&n);
			long long code;
			int counts;
			for (int test = 0; test < n; test++) {
				//if (test > 100) break; 
				fscanf(pFILE, "%lld\t%d",&code, &counts);
				maps[code] += ((1LL << (ttt * 10)) * counts);
				maxs=max(maxs,counts);
			}
			fclose(pFILE);			
			//printf("%lld", ttt);

	//		cout<<s<<endl;		
		}	
	}
	closedir(dp);
	cout<<maxs<<endl;
	cout<<maps.size()<<endl;
	long long tmp;
	for (auto& x: maps) {
		printf("%lld",x.first);
		tmp = x.second;
		for (int i = 0; i < 6; i++) {
			printf("\t%d", ((tmp & (1023LL<<(i*10))) >> (i*10)) );
		}
		printf("\n");
  	}
	
	return 0;
}

