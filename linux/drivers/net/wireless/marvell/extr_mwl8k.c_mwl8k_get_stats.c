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
struct ieee80211_low_level_stats {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int mwl8k_cmd_get_stat (struct ieee80211_hw*,struct ieee80211_low_level_stats*) ; 

__attribute__((used)) static int mwl8k_get_stats(struct ieee80211_hw *hw,
			   struct ieee80211_low_level_stats *stats)
{
	return mwl8k_cmd_get_stat(hw, stats);
}