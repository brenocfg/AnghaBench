#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;

/* Variables and functions */
#define  NL80211_DFS_ETSI 131 
#define  NL80211_DFS_FCC 130 
#define  NL80211_DFS_JP 129 
#define  NL80211_DFS_UNSET 128 
 int RSI_REGION_ETSI ; 
 int RSI_REGION_FCC ; 
 int RSI_REGION_TELEC ; 
 int RSI_REGION_WORLD ; 

__attribute__((used)) static int rsi_map_region_code(enum nl80211_dfs_regions region_code)
{
	switch (region_code) {
	case NL80211_DFS_FCC:
		return RSI_REGION_FCC;
	case NL80211_DFS_ETSI:
		return RSI_REGION_ETSI;
	case NL80211_DFS_JP:
		return RSI_REGION_TELEC;
	case NL80211_DFS_UNSET:
		return RSI_REGION_WORLD;
	}
	return RSI_REGION_WORLD;
}