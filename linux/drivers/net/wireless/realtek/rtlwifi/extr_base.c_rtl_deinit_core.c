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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_c2hcmd_launcher (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_free_entries_from_ack_queue (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl_free_entries_from_scan_list (struct ieee80211_hw*) ; 

void rtl_deinit_core(struct ieee80211_hw *hw)
{
	rtl_c2hcmd_launcher(hw, 0);
	rtl_free_entries_from_scan_list(hw);
	rtl_free_entries_from_ack_queue(hw, false);
}