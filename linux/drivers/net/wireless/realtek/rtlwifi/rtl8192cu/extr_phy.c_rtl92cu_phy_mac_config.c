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
 int _rtl92cu_phy_config_mac_with_headerfile (struct ieee80211_hw*) ; 

bool rtl92cu_phy_mac_config(struct ieee80211_hw *hw)
{
	bool rtstatus;

	rtstatus = _rtl92cu_phy_config_mac_with_headerfile(hw);
	return rtstatus;
}