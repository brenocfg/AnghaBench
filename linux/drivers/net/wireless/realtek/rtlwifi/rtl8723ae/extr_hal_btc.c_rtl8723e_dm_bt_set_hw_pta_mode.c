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
struct TYPE_2__ {int hw_coexist_all_off; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BT_PTA_MODE_ON ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_hw_pta_mode(struct ieee80211_hw *hw, bool b_mode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (BT_PTA_MODE_ON == b_mode) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE, "PTA mode on\n");
		/*  Enable GPIO 0/1/2/3/8 pins for bt */
		rtl_write_byte(rtlpriv, 0x40, 0x20);
		rtlpriv->btcoexist.hw_coexist_all_off = false;
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE, "PTA mode off\n");
		rtl_write_byte(rtlpriv, 0x40, 0x0);
	}
}