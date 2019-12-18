#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bt_active_zero_cnt; int cur_bt_disabled; int pre_bt_disabled; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int high_priority_tx; int high_priority_rx; int low_priority_tx; int low_priority_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ hal_coex_8723 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_bt_enable_disable_check(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	bool bt_alife = true;

	if (hal_coex_8723.high_priority_tx == 0 &&
	    hal_coex_8723.high_priority_rx == 0 &&
	    hal_coex_8723.low_priority_tx == 0 &&
	    hal_coex_8723.low_priority_rx == 0) {
		bt_alife = false;
	}
	if (hal_coex_8723.high_priority_tx == 0xeaea &&
	    hal_coex_8723.high_priority_rx == 0xeaea &&
	    hal_coex_8723.low_priority_tx == 0xeaea &&
	    hal_coex_8723.low_priority_rx == 0xeaea) {
		bt_alife = false;
	}
	if (hal_coex_8723.high_priority_tx == 0xffff &&
	    hal_coex_8723.high_priority_rx == 0xffff &&
	    hal_coex_8723.low_priority_tx == 0xffff &&
	    hal_coex_8723.low_priority_rx == 0xffff) {
		bt_alife = false;
	}
	if (bt_alife) {
		rtlpriv->btcoexist.bt_active_zero_cnt = 0;
		rtlpriv->btcoexist.cur_bt_disabled = false;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "8723A BT is enabled !!\n");
	} else {
		rtlpriv->btcoexist.bt_active_zero_cnt++;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "8723A bt all counters=0, %d times!!\n",
			 rtlpriv->btcoexist.bt_active_zero_cnt);
		if (rtlpriv->btcoexist.bt_active_zero_cnt >= 2) {
			rtlpriv->btcoexist.cur_bt_disabled = true;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "8723A BT is disabled !!\n");
		}
	}
	if (rtlpriv->btcoexist.pre_bt_disabled !=
		rtlpriv->btcoexist.cur_bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST,
			 DBG_TRACE, "8723A BT is from %s to %s!!\n",
			 (rtlpriv->btcoexist.pre_bt_disabled ?
				"disabled" : "enabled"),
			 (rtlpriv->btcoexist.cur_bt_disabled ?
				"disabled" : "enabled"));
		rtlpriv->btcoexist.pre_bt_disabled
			= rtlpriv->btcoexist.cur_bt_disabled;
	}
}