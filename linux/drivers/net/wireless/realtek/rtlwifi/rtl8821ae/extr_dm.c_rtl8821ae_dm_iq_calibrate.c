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
struct rtl_mac {scalar_t__ link_state; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct rtl_dm {int linked_interval; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  rtl8812ae_phy_iq_calibrate (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_phy_iq_calibrate (struct ieee80211_hw*,int) ; 
 struct rtl_dm* rtl_dm (int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8821ae_dm_iq_calibrate(struct ieee80211_hw *hw)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (mac->link_state >= MAC80211_LINKED) {
		if (rtldm->linked_interval < 3)
			rtldm->linked_interval++;

		if (rtldm->linked_interval == 2) {
			if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
				rtl8812ae_phy_iq_calibrate(hw, false);
			else
				rtl8821ae_phy_iq_calibrate(hw, false);
		}
	} else {
		rtldm->linked_interval = 0;
	}
}