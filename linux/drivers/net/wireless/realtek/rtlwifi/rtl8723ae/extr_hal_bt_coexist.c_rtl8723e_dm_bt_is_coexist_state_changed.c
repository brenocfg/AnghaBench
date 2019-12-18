#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ previous_state; scalar_t__ cstate; scalar_t__ previous_state_h; scalar_t__ cstate_h; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl8723e_dm_bt_is_coexist_state_changed(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if ((rtlpriv->btcoexist.previous_state == rtlpriv->btcoexist.cstate) &&
	    (rtlpriv->btcoexist.previous_state_h ==
	     rtlpriv->btcoexist.cstate_h))
		return false;
	return true;
}