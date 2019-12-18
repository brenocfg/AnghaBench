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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int fw_coexist_all_off; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_fill_h2c_cmd (struct ieee80211_hw*,int,int,int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_fw_dec_bt_pwr(
		struct ieee80211_hw *hw, bool dec_bt_pwr)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = {0};

	h2c_parameter[0] = 0;

	if (dec_bt_pwr) {
		h2c_parameter[0] |= BIT(1);
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		 "[BTCoex], decrease Bt Power : %s, write 0x21=0x%x\n",
		 (dec_bt_pwr ? "Yes!!" : "No!!"), h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x21, 1, h2c_parameter);
}