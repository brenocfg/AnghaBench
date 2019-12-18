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
struct TYPE_2__ {int sw_coexist_all_off; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_sw_coex_all_off_8723a (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8723e_dm_bt_sw_coex_all_off(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		 "rtl8723e_dm_bt_sw_coex_all_off()\n");

	if (rtlpriv->btcoexist.sw_coexist_all_off)
		return;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		 "rtl8723e_dm_bt_sw_coex_all_off(), real Do\n");
	rtl8723e_dm_bt_sw_coex_all_off_8723a(hw);
	rtlpriv->btcoexist.sw_coexist_all_off = true;
}