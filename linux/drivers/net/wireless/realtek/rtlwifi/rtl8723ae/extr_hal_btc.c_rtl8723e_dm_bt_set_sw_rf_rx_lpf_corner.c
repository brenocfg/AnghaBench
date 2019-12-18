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
struct TYPE_2__ {int sw_coexist_all_off; int bt_rfreg_origin_1e; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT_RF_RX_LPF_CORNER_RESUME ; 
 scalar_t__ BT_RF_RX_LPF_CORNER_SHRINK ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8723e_phy_set_rf_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner(struct ieee80211_hw *hw,
						   u8 type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (BT_RF_RX_LPF_CORNER_SHRINK == type) {
		/* Shrink RF Rx LPF corner, 0x1e[7:4]=1111 ==> [11:4] */
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "Shrink RF Rx LPF corner!!\n");
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A, 0x1e,
					0xfffff, 0xf0ff7);
		rtlpriv->btcoexist.sw_coexist_all_off = false;
	} else if (BT_RF_RX_LPF_CORNER_RESUME == type) {
		/*Resume RF Rx LPF corner*/
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "Resume RF Rx LPF corner!!\n");
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A, 0x1e, 0xfffff,
					rtlpriv->btcoexist.bt_rfreg_origin_1e);
	}
}