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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ETH_SS_STATS ; 
 int MAC80211_HWSIM_SSTATS_LEN ; 

__attribute__((used)) static int mac80211_hwsim_get_et_sset_count(struct ieee80211_hw *hw,
					    struct ieee80211_vif *vif, int sset)
{
	if (sset == ETH_SS_STATS)
		return MAC80211_HWSIM_SSTATS_LEN;
	return 0;
}