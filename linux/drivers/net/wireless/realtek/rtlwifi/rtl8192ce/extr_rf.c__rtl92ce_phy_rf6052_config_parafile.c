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
typedef  size_t u8 ;
typedef  int u32 ;
struct rtl_phy {size_t num_total_rfpath; struct bb_reg_def* phyreg_def; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct bb_reg_def {int /*<<< orphan*/  rfintfs; int /*<<< orphan*/  rfhssi_para2; int /*<<< orphan*/  rfintfo; int /*<<< orphan*/  rfintfe; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int B3WIREADDREAALENGTH ; 
 int B3WIREDATALENGTH ; 
 int BRFSI_RFENV ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int rtl92c_phy_config_rf_with_headerfile (struct ieee80211_hw*,int) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool _rtl92ce_phy_rf6052_config_parafile(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 u4_regvalue = 0;
	u8 rfpath;
	bool rtstatus = true;
	struct bb_reg_def *pphyreg;

	for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {

		pphyreg = &rtlphy->phyreg_def[rfpath];

		switch (rfpath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			u4_regvalue = rtl_get_bbreg(hw, pphyreg->rfintfs,
						    BRFSI_RFENV);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			u4_regvalue = rtl_get_bbreg(hw, pphyreg->rfintfs,
						    BRFSI_RFENV << 16);
			break;
		}

		rtl_set_bbreg(hw, pphyreg->rfintfe, BRFSI_RFENV << 16, 0x1);
		udelay(1);

		rtl_set_bbreg(hw, pphyreg->rfintfo, BRFSI_RFENV, 0x1);
		udelay(1);

		rtl_set_bbreg(hw, pphyreg->rfhssi_para2,
			      B3WIREADDREAALENGTH, 0x0);
		udelay(1);

		rtl_set_bbreg(hw, pphyreg->rfhssi_para2, B3WIREDATALENGTH, 0x0);
		udelay(1);

		switch (rfpath) {
		case RF90_PATH_A:
			rtstatus = rtl92c_phy_config_rf_with_headerfile(hw,
						(enum radio_path)rfpath);
			break;
		case RF90_PATH_B:
			rtstatus = rtl92c_phy_config_rf_with_headerfile(hw,
						(enum radio_path)rfpath);
			break;
		case RF90_PATH_C:
			break;
		case RF90_PATH_D:
			break;
		}

		switch (rfpath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			rtl_set_bbreg(hw, pphyreg->rfintfs,
				      BRFSI_RFENV, u4_regvalue);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			rtl_set_bbreg(hw, pphyreg->rfintfs,
				      BRFSI_RFENV << 16, u4_regvalue);
			break;
		}

		if (!rtstatus) {
			RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
				 "Radio[%d] Fail!!\n", rfpath);
			return false;
		}

	}

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "<---\n");
	return rtstatus;
}