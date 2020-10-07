#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class JSON
{
		boost::property_tree::ptree TREE;
	public:
		JSON(const std::string& file);
		float CHECK(float run, float lumi);
};

JSON::JSON(const std::string& file)
{
	std::cout<<"Loading JSON file: "<<file<<"..."<<std::endl;
	boost::property_tree::read_json(file, TREE);
	std::cout<<"... Done!"<<std::endl;
}

float JSON::CHECK(float run, float lumi)
{
	for ( const auto& runEntry : TREE )
	{
		if (std::stoul(runEntry.first) == (unsigned int)run)
		{
			for ( const auto& lrEntry : runEntry.second )
			{
				const auto lrNd = lrEntry.second;
				unsigned int lumStart = std::stoul((lrNd.begin())->second.data());
				unsigned int lumEnd = std::stoul((++lrNd.begin())->second.data());
				unsigned int L = (unsigned int) lumi;
				if ((L < lumEnd) && (L > lumStart))
				{
					return 1.;
				}
			}
		}
	}
	std::cout<<"BAD RUN/LUMI: "<< run << ", " << lumi<<std::endl;
	return 0.;
}
