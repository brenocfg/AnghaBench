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
typedef  enum qlink_dfs_state { ____Placeholder_qlink_dfs_state } qlink_dfs_state ;
typedef  enum nl80211_dfs_state { ____Placeholder_nl80211_dfs_state } nl80211_dfs_state ;

/* Variables and functions */
#define  NL80211_DFS_AVAILABLE 130 
#define  NL80211_DFS_UNAVAILABLE 129 
#define  NL80211_DFS_USABLE 128 
 int QLINK_DFS_AVAILABLE ; 
 int QLINK_DFS_UNAVAILABLE ; 
 int QLINK_DFS_USABLE ; 

enum qlink_dfs_state qlink_utils_dfs_state_cfg2q(enum nl80211_dfs_state state)
{
	switch (state) {
	case NL80211_DFS_USABLE:
		return QLINK_DFS_USABLE;
	case NL80211_DFS_AVAILABLE:
		return QLINK_DFS_AVAILABLE;
	case NL80211_DFS_UNAVAILABLE:
	default:
		return QLINK_DFS_UNAVAILABLE;
	}
}