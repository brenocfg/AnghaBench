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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DESC92C_RATE11M 151 
#define  DESC92C_RATE12M 150 
#define  DESC92C_RATE18M 149 
#define  DESC92C_RATE1M 148 
#define  DESC92C_RATE24M 147 
#define  DESC92C_RATE2M 146 
#define  DESC92C_RATE36M 145 
#define  DESC92C_RATE48M 144 
#define  DESC92C_RATE54M 143 
#define  DESC92C_RATE5_5M 142 
#define  DESC92C_RATE6M 141 
#define  DESC92C_RATE9M 140 
#define  DESC92C_RATEMCS0 139 
#define  DESC92C_RATEMCS1 138 
#define  DESC92C_RATEMCS10 137 
#define  DESC92C_RATEMCS11 136 
#define  DESC92C_RATEMCS2 135 
#define  DESC92C_RATEMCS3 134 
#define  DESC92C_RATEMCS4 133 
#define  DESC92C_RATEMCS5 132 
#define  DESC92C_RATEMCS6 131 
#define  DESC92C_RATEMCS7 130 
#define  DESC92C_RATEMCS8 129 
#define  DESC92C_RATEMCS9 128 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKBYTE1 ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 scalar_t__ RF90_PATH_A ; 
 int /*<<< orphan*/  RTXAGC_A_CCK1_MCS32 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS03_MCS00 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS07_MCS04 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS11_MCS08 ; 
 int /*<<< orphan*/  RTXAGC_A_RATE18_06 ; 
 int /*<<< orphan*/  RTXAGC_A_RATE54_24 ; 
 int /*<<< orphan*/  RTXAGC_B_CCK11_A_CCK2_11 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8723_phy_set_bb_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8723be_phy_set_txpower_index(struct ieee80211_hw *hw,
					     u8 power_index, u8 path, u8 rate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	if (path == RF90_PATH_A) {
		switch (rate) {
		case DESC92C_RATE1M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_CCK1_MCS32,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATE2M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_B_CCK11_A_CCK2_11,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATE5_5M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_B_CCK11_A_CCK2_11,
					       MASKBYTE2, power_index);
			break;
		case DESC92C_RATE11M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_B_CCK11_A_CCK2_11,
					       MASKBYTE3, power_index);
			break;

		case DESC92C_RATE6M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE0, power_index);
			break;
		case DESC92C_RATE9M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATE12M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE2, power_index);
			break;
		case DESC92C_RATE18M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE3, power_index);
			break;

		case DESC92C_RATE24M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE0, power_index);
			break;
		case DESC92C_RATE36M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATE48M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE2, power_index);
			break;
		case DESC92C_RATE54M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE3, power_index);
			break;

		case DESC92C_RATEMCS0:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE0, power_index);
			break;
		case DESC92C_RATEMCS1:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATEMCS2:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE2, power_index);
			break;
		case DESC92C_RATEMCS3:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE3, power_index);
			break;

		case DESC92C_RATEMCS4:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE0, power_index);
			break;
		case DESC92C_RATEMCS5:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATEMCS6:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE2, power_index);
			break;
		case DESC92C_RATEMCS7:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE3, power_index);
			break;

		case DESC92C_RATEMCS8:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE0, power_index);
			break;
		case DESC92C_RATEMCS9:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE1, power_index);
			break;
		case DESC92C_RATEMCS10:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE2, power_index);
			break;
		case DESC92C_RATEMCS11:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE3, power_index);
			break;

		default:
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid Rate!!\n");
			break;
		}
	} else {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid RFPath!!\n");
	}
}