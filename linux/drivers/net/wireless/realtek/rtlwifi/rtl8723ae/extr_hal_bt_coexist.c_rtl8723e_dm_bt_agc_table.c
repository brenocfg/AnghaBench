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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int sw_coexist_all_off; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT_AGCTABLE_OFF ; 
 scalar_t__ BT_AGCTABLE_ON ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF_RX_AGC_HP ; 
 int /*<<< orphan*/  RF_RX_G1 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8723e_phy_set_rf_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

void rtl8723e_dm_bt_agc_table(struct ieee80211_hw *hw, u8 type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (type == BT_AGCTABLE_OFF) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "[BT]AGCTable Off!\n");
		rtl_write_dword(rtlpriv, 0xc78, 0x641c0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x631d0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x621e0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x611f0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x60200001);

		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x32000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x71000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0xb0000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0xfc000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_G1, 0xfffff, 0x30355);
	} else if (type == BT_AGCTABLE_ON) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "[BT]AGCTable On!\n");
		rtl_write_dword(rtlpriv, 0xc78, 0x4e1c0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x4d1d0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x4c1e0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x4b1f0001);
		rtl_write_dword(rtlpriv, 0xc78, 0x4a200001);

		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0xdc000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x90000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x51000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x12000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_G1, 0xfffff, 0x00355);

		rtlpriv->btcoexist.sw_coexist_all_off = false;
	}
}