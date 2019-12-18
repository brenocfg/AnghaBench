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
struct TYPE_2__ {int dm_initialgain_enable; int dm_flag; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int DYNAMIC_FUNC_DIG ; 
 int /*<<< orphan*/  rtl92c_dm_ctrl_initgain_by_twoport (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92c_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (rtlpriv->dm.dm_initialgain_enable == false)
		return;
	if (!(rtlpriv->dm.dm_flag & DYNAMIC_FUNC_DIG))
		return;

	rtl92c_dm_ctrl_initgain_by_twoport(hw);
}