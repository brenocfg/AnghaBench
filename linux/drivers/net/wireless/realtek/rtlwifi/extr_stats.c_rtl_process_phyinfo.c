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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_stats {int /*<<< orphan*/  packet_matchbssid; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_process_pwdb (struct ieee80211_hw*,struct rtl_stats*) ; 
 int /*<<< orphan*/  rtl_process_ui_link_quality (struct ieee80211_hw*,struct rtl_stats*) ; 
 int /*<<< orphan*/  rtl_process_ui_rssi (struct ieee80211_hw*,struct rtl_stats*) ; 

void rtl_process_phyinfo(struct ieee80211_hw *hw, u8 *buffer,
			 struct rtl_stats *pstatus)
{

	if (!pstatus->packet_matchbssid)
		return;

	rtl_process_ui_rssi(hw, pstatus);
	rtl_process_pwdb(hw, pstatus);
	rtl_process_ui_link_quality(hw, pstatus);
}