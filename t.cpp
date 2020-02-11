#include <unordered_map>
#include <iterator>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include <fstream>
using namespace std;


struct info_node
{
	int libel;
	vector<int>label;
};

struct node_struct
{
	vector<int> label;
	int poid;
};

struct dag_freq
{
	int id;
	int frequence;
};
unordered_map<int, vector<int>> parcour_longueur(vector<vector<int>>& in)
{
	int s = 0;
	unordered_map<int, vector<int>> a;
	vector<int> taille;
	a[0].push_back(0);
	///TreeMap<Integer, ArrayList<Integer>>hash=new TreeMap<Integer, ArrayList<Integer>>();
	vector<int> su;
	vector<int> sub;
	for (int i = 0; i < in.size(); i++)
	{

		taille.push_back(0);

	}



	for (int src = 0; src < in.size(); src++)
	{

		for (int i = 0; i < in[src].size(); i++)
		{
			s = in[src][i];
			taille[s] = taille[src] + 1;
			su.push_back(s);

		}


		//sub = su;
		if (a.find(taille[s]) == a.end())
		{

			su.insert(su.end(), a[(taille[s])].begin(), a[(taille[s])].end());
		}
		//a::put(taille[s],sub);
		a[taille[s]].insert(a[(taille[s])].end(), su.begin(), su.end());
		su.clear();


	}

	return a;
}


int maxArray(vector<int> list)
{
	int max = list[0];

	for (int i = 1; i < list.size(); i++)
	{
		if (max < list[i])
		{
			max = list[i];
		}

	}
	return max;
}

void sort_one(vector<int>& has)

{

	vector<int> list_to_sort;
	int m = maxArray(has);

	vector<vector<int>> list(m + 1);
	for (int i : has)
	{
		list[i].push_back(i);

	}

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].size() > 0)
		{
			list_to_sort.insert(list_to_sort.end(), list[i].begin(), list[i].end());
		}

	}

	has = list_to_sort;

}



vector<vector<int>> trier(vector<vector<int>> a)
{


	vector<int> max;
	for (int i = 0; i < a.size(); i++)
	{
		max.push_back(maxArray(a[i]));
	}

	int max_v = maxArray(max);
	vector<std::vector<int>> bucket;
	vector<int> vide_1;

	for (int i = 0; i <= max_v; i++)
	{
		bucket.push_back(vide_1);
	}

	int k = a[0].size();
	k--;

	for (int i = k; i >= 0; i--)
	{

		for (int l = max_v; l >= 0; l--)
		{
			bucket[l] = vide_1;
		}



		for (vector<int> tmp : a)
		{

			if (!tmp.empty())
			{
				if (bucket[tmp[i]].empty())
				{
					bucket[tmp[i]] = tmp;

				}
				else
				{

					bucket[tmp[i]].insert(bucket[tmp[i]].end(), tmp.begin(), tmp.end());
				}

			}
		}

		a.clear();
		for (vector<int> tuples : bucket)
		{

			if (!tuples.empty())
			{
				if (tuples.size() > k + 1)
				{

					for (int j = 0; j < tuples.size(); j = j + k + 1)
					{

						vector<int> sub;
						for (int ab = j; ab <= j + k; ab++)
						{
							sub.push_back(tuples[ab]);
						}
						a.push_back(sub);

					}


				}
				else
				{
					a.push_back(tuples);
				}

			}
		}

	}

	return a;
}


int length_max(vector<vector<int>> inputs)
{
	int max = inputs[0].size();
	for (int i = 1; i < inputs.size(); i++)
	{
		if (inputs[i].size() > max)
		{
			max = inputs[i].size();
		}
	}
	return max;

}

vector<vector<int>>  assign_to_list(vector<vector<int>> inputs)
{
	int l_max = length_max(inputs);

	std::vector<int> vide;
	std::vector<std::vector<int>> Length;
	for (int l = 0; l <= l_max; l++)
	{
		Length.push_back(vide);
	}


	for (auto input : inputs)
	{
		if (Length[input.size()].empty())
		{
			Length[input.size()] = input;
		}
		else
		{
			Length[input.size()].insert(Length[input.size()].end(), input.begin(), input.end());
		}
	}
	return Length;

}







deque<vector<int>> trier_advenced(vector<vector<int>> a)
{

	vector<std::vector<int>> conteneur;
	vector<int> max;
	for (int i = 0; i < a.size(); i++)
	{
		max.push_back(maxArray(a[i]));
	}

	int max_v = maxArray(max);
	int l_max = length_max(a);
	vector<vector<vector<int>>> bucket;
	vector<vector<int>> vide_1;
	std::vector<int> emp;
	std::vector<int> tmp;
	vector<vector<int>> Length = assign_to_list(a);
	deque<vector<int>> deq;
	for (int i = 0; i <= max_v; i++)
	{
		bucket.push_back(vide_1);
	}
	for (int l = l_max; l > 0; l--)
	{

		if (!Length[l].empty())
		{

			if (Length[l].size() > l)
			{
				int Length_inputs = Length[l].size();
				int p = 0;
				int Longeur = l;
				while (p < Length_inputs)
				{

					vector<int> sub;
					for (int q = p; q < Longeur; q++)
					{
						sub.push_back(Length[l][q]);
					}


					deq.push_front(sub);
					p += l;
					Longeur += l;

				}
			}
			else
			{
				deq.push_front(Length[l]);
			}



		}


		for (vector<int>tmp : deq)
		{

			bucket[tmp[l - 1]].push_back(tmp);
		}


		deq.clear();

		for (vector<vector<int>> tuples : bucket)
		{
			if (!tuples.empty())
			{

				for (vector<int> tuple : tuples)

					deq.push_back(tuple);


			}
		}






		for (int i = 0; i <= max_v; i++)
		{
			bucket[i] = vide_1;
		}


	}


	return deq;

}

vector<vector<int>> assigne_same_length(vector<vector<int>> l)
{
	int l_max = length_max(l);
	for (int j = 0; j < l.size(); j++)
	{
		if (l[j].size() < l_max)
		{

			int i = l[j].size();
			while (i < l_max)
			{
				l[j].push_back(0);
				i++;
			}
		}
	}
	return l;
}


bool iso_between_to_tree(vector<vector<int>>t1, vector<vector<int>> t2)
{
	unordered_map<int, vector<int>>u1 = parcour_longueur(t1);
	unordered_map<int, vector<int>>u2 = parcour_longueur(t2);
	vector<info_node>v1(t1.size());
	vector<info_node>v2(t2.size());

	if (t1.size() != t2.size() || u1.size() != u2.size())
	{
		return false;
	}
	for (int i = 0; i < t1.size(); i++)
	{
		if (t1[i].empty())
		{

			v1[i].libel = 0;
		}
	}
	for (int j = 0; j < t2.size(); j++)
	{
		if (t2[j].empty())
		{
			v2[j].libel = 0;
		}
	}
	int i = u1.size() - 2;

	vector<vector<int>>level_tree_1;
	vector<vector<int>>level_tree_2;
	while (i >= 0)
	{
		vector<int> w1 = u1[i];
		vector<int> w2 = u2[i];


		for (int j : w1)
		{
			if (!t1[j].empty())
			{
				for (int c1 : t1[j])
				{
					v1[j].label.push_back(v1[c1].libel);
				}
				sort_one(v1[j].label);
				level_tree_1.push_back(v1[j].label);

			}
		}
		for (int j : w2)
		{
			if (!t2[j].empty())
			{
				for (int c1 : t2[j])
				{
					v2[j].label.push_back(v2[c1].libel);
				}

				sort_one(v2[j].label);
				level_tree_2.push_back(v2[j].label);

			}
		}


		deque<vector<int>>d1 = trier_advenced(level_tree_1);
		unique(d1.begin(), d1.end());
		deque<vector<int>>d2 = trier_advenced(level_tree_2);
		unique(d2.begin(), d2.end());
		if (d1 == d2)
		{

			for (int j : w1)

				v1[j].libel = find(d1.begin(), d1.end(), v1[j].label) - d1.begin() + 1;

			for (int j : w2)

				v2[j].libel = find(d2.begin(), d2.end(), v2[j].label) - d2.begin() + 1;


			level_tree_1.clear();
			level_tree_2.clear();
		}
		else
			return false;


		i--;
	}





	return true;
}

int parent_of_node(vector<vector<int>>t, int n)
{
	for (int i = 0; i < t.size(); i++)
	{
		for (int j = 0; j < t[i].size(); j++)
		{
			if (t[i][j] == n)
				return i;
		}
	}
}

vector<int>make_correspondence_between_label_and_node(vector<node_struct>v1, vector<int>v, deque<vector<int>>label_node)
{
	vector<int>order;
	for (int i = 0; i < label_node.size(); i++)
	{
		/*for (int h = 0; h < label_node[i].size(); h++)
		{
			cout << label_node[i][h];
		}*/
		//cout << "\n";
		auto it = v.begin();
		int j = 0;
		while (it != v.end())
		{
			j++;
			if (v1[*it].label == label_node[i])
			{

				order.push_back(*it);
				it = v.erase(it);
				break;
			}
			++it;

		}
	}
	return order;
}
vector<int> split_to_one_list(vector<node_struct>t)
{
	vector<int>rez;
	for (int i = 0; i < t.size(); i++)
	{


		rez.push_back(t[i].poid);

	}
	return rez;
}


vector<node_struct> compression(vector<vector<int>> v)
{
	deque<vector<int>>d;
	int parent;
	unordered_map<int, vector<int>>u1 = parcour_longueur(v);
	vector<node_struct>v1(v.size());
	int Size = v.size() - 1;
	int stage = u1.size();

	for (int i = Size; i > 0; i--)
	{

		if (v[i].empty())
		{

			v1[i].poid = 1;
			parent = parent_of_node(v, i);
			v1[parent].label.push_back(1);

		}


	}

	for (int i = stage - 2; i > 0; i--)
	{
		int max = 0;
		vector<int>node_to_label;
		vector<vector<int>>label_node;
		vector<int>spl;
		for (int c : u1[i])
		{

			if (!v[c].empty())
			{


				label_node.push_back(v1[c].label);
			}
		}
		d = trier_advenced(label_node);

		node_to_label = make_correspondence_between_label_and_node(v1, u1[i], d);
		spl = split_to_one_list(v1);
		max = maxArray(spl);

		v1[node_to_label[0]].poid = max + 1;
		parent = parent_of_node(v, node_to_label[0]);
		v1[parent].label.push_back(max + 1);
		for (int i = 1; i < node_to_label.size(); i++)
		{
			int node_i_minus_1 = node_to_label[i - 1];
			int node_i = node_to_label[i];

			if (v1[node_i].label == v1[node_i_minus_1].label)
				v1[node_i].poid = v1[node_i_minus_1].poid;
			else
			{
				v1[node_i].poid = v1[node_i_minus_1].poid + 1;

			}
			parent = parent_of_node(v, node_i);
			v1[parent].label.push_back(v1[node_i].poid);

		}

	}
	vector<int>all_poid;
	for (int i = 0; i < v1.size(); i++)
	{

		all_poid.push_back(v1[i].poid);
	}
	int max = maxArray(all_poid);
	v1[0].poid = max + 1;
	return v1;
}

vector<int> frequence_of_apparition(vector<vector<int>> v)
{
	vector<node_struct>n_s = compression(v);
	vector<int> frequence(n_s[0].poid + 1);

	for (int i = 0; i < v.size(); i++)
	{
		for (int j : v[i])
		{
			frequence[n_s[j].poid] += 1;
		}
	}

	return frequence;
}

vector<unordered_set<int>> transform_to_dag(vector<vector<int>> v)
{
	vector<node_struct>n_s = compression(v);
	int Size = n_s[0].poid + 1;
	vector<unordered_set<int>>dag(Size);
	for (int i = 0; i < v.size(); i++)
	{
		for (int j : v[i])
		{
			dag[n_s[i].poid].insert(n_s[j].poid);
		}
	}
	return dag;
}

vector<vector<int>>read_file_txt(string path)
{
	ifstream fichier(path,ios::in);
	vector<string>v_s;
	vector<vector<string>>v_v_s;
	vector<int>tr;
	vector<vector<int>>tree;
	string s;
	while(getline(fichier,s))
	{
		v_s.push_back(s);
		v_v_s.push_back(v_s);
		v_s.clear();
	}

	for(int i=0;i<v_v_s.size();i++)
	{
		for(int j=0;j<v_v_s[i].size();j++)
		{
			int k=0;
			for(char c:v_v_s[i][j])
			{
				if(c=='1')
					tr.push_back(k);
				k++;
			}
			tree.push_back(tr);
			tr.clear();
		}
	}
	return tree;
}

void text_file_output(vector<unordered_set<int>>un , string out)
{

	vector<vector<int>>tree(un.size());

	for(int j=0;j<tree.size();j++)
	{

		for(int i=0;i<un.size();i++)
		{
			tree[j].push_back(0);
		}
	}
	int count=0;
	ofstream file(out);
	for(unordered_set<int> u:un)
	{
		if(!u.empty())
		{

			for(int a:u)
			{
				tree[count][a]=1;
			}

		}
		count++;
	}
	string b;
	for(int j=0;j<tree.size();j++)
	{
		for(int k=0;k<tree[j].size();k++)
		{
			b+=to_string(tree[j][k]);

		}
		file<<b<<"\n";
		b.clear();
	}


}
int main(int argc, char *argv[])
{

	vector<vector<int>>ar={{1,2},{3,4},{5},{},{6},{7},{},{}};
	vector<vector<int>>ar2={{1,2},{3,4},{5},{6},{},{7},{},{}};

	vector<vector<int>>ar3 = { {1,2,3},{4,5,6},{7,8},{9,10,11},{},{},{},{},{},{},{},{} };


	bool iso= iso_between_to_tree(ar,ar2);
	if(iso)

		cout<<"les arbres ar et ar2 sont isomprphe\n";
	else
		cout<<"les arbres ar et ar2 ne sont pas isomorphe \n";

	cout<<"====================compression============================\n";

	/*vector<unordered_set<int>> un=transform_to_dag(ar3);
	text_file_output(un);
	string son;
	vector<int>frequences = frequence_of_apparition(ar3);
	for (int i = 2; i < un.size(); i++)
	{
		if (un[i].size() > 1)
			son = "the sons of";
		else
			son = "the son of";
		cout << son<<" "<<i<<"==>{";
		for (int j : un[i])
		{
			cout << " " << j;
		}

		cout << "} and appeared "<<frequences[i]<<" times in the initial tree \n";
	}

	//string a="bonjour tout le monde";
	//boost::split(a, input, boost::is_any_of("\t"));
	vector<string> v_lignes;
	vector<vector<int>>tree=read_file_txt("/home/samir/Bureau/samir.txt");
	for(int i=0;i<tree.size();i++)
	{
		for(int a:tree[i])
		{
			cout<<a;
		}
		cout<<"\n";
	}*/

	vector<vector<int>>tree=read_file_txt(argv[1]);
	vector<unordered_set<int>> un=transform_to_dag(tree);
		text_file_output(un,argv[2]);
		string son;
		vector<int>frequences = frequence_of_apparition(tree);
		for (int i = 2; i < un.size(); i++)
		{
			if (un[i].size() > 1)
				son = "the sons of";
			else
				son = "the son of";
			cout << son<<" "<<i<<"==>{";
			for (int j : un[i])
			{
				cout << " " << j;
			}

			cout << "} and appeared "<<frequences[i]<<" times in the initial tree \n";
		}


	return 0;


}
