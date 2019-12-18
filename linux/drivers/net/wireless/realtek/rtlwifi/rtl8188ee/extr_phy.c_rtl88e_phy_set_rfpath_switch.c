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
 int /*<<< orphan*/  _rtl88e_phy_set_rfpath_switch (struct ieee80211_hw*,int,int) ; 

void rtl88e_phy_set_rfpath_switch(struct ieee80211_hw *hw, bool bmain)
{
	_rtl88e_phy_set_rfpath_switch(hw, bmain, false);
}