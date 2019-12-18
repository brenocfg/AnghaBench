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
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92c_phy_set_rfpath_switch (struct ieee80211_hw*,int,int) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

void rtl92c_phy_set_rfpath_switch(struct ieee80211_hw *hw, bool bmain)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (IS_92C_SERIAL(rtlhal->version))
		_rtl92c_phy_set_rfpath_switch(hw, bmain, true);
	else
		_rtl92c_phy_set_rfpath_switch(hw, bmain, false);
}