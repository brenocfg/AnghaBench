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
struct rtl_hal {scalar_t__ macphymode; scalar_t__ current_bandtype; int interfaceindex; int during_mac1init_radioa; int during_mac0init_radiob; } ;
struct rtl_phy {scalar_t__ rf_type; int num_total_rfpath; struct bb_reg_def* phyreg_def; } ;
struct rtl_priv {struct rtl_hal rtlhal; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct bb_reg_def {int /*<<< orphan*/  rfintfs; int /*<<< orphan*/  rfhssi_para2; int /*<<< orphan*/  rfintfo; int /*<<< orphan*/  rfintfe; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int B3WIREADDRESSLENGTH ; 
 int B3WIREDATALENGTH ; 
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 int BRFSI_RFENV ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ DUALMAC_DUALPHY ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 scalar_t__ RF_1T1R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  radioa_txt ; 
 int /*<<< orphan*/  radiob_txt ; 
 int rtl92d_phy_config_rf_with_headerfile (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtl92d_phy_enable_anotherphy (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92d_phy_powerdown_anotherphy (struct ieee80211_hw*,int) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool rtl92d_phy_rf6052_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	bool rtstatus = true;
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 u4_regvalue = 0;
	u8 rfpath;
	struct bb_reg_def *pphyreg;
	bool mac1_initradioa_first = false, mac0_initradiob_first = false;
	bool need_pwrdown_radioa = false, need_pwrdown_radiob = false;
	bool true_bpath = false;

	if (rtlphy->rf_type == RF_1T1R)
		rtlphy->num_total_rfpath = 1;
	else
		rtlphy->num_total_rfpath = 2;

	/* Single phy mode: use radio_a radio_b config path_A path_B */
	/* seperately by MAC0, and MAC1 needn't configure RF; */
	/* Dual PHY mode:MAC0 use radio_a config 1st phy path_A, */
	/* MAC1 use radio_b config 2nd PHY path_A. */
	/* DMDP,MAC0 on G band,MAC1 on A band. */
	if (rtlhal->macphymode == DUALMAC_DUALPHY) {
		if (rtlhal->current_bandtype == BAND_ON_2_4G &&
		    rtlhal->interfaceindex == 0) {
			/* MAC0 needs PHY1 load radio_b.txt.
			 * Driver use DBI to write. */
			if (rtl92d_phy_enable_anotherphy(hw, true)) {
				rtlphy->num_total_rfpath = 2;
				mac0_initradiob_first = true;
			} else {
				/* We think if MAC1 is ON,then radio_a.txt and
				 * radio_b.txt has been load. */
				return rtstatus;
			}
		} else if (rtlhal->current_bandtype == BAND_ON_5G &&
			   rtlhal->interfaceindex == 1) {
			/* MAC1 needs PHY0 load radio_a.txt.
			 * Driver use DBI to write. */
			if (rtl92d_phy_enable_anotherphy(hw, false)) {
				rtlphy->num_total_rfpath = 2;
				mac1_initradioa_first = true;
			} else {
				/* We think if MAC0 is ON,then radio_a.txt and
				 * radio_b.txt has been load. */
				return rtstatus;
			}
		} else if (rtlhal->interfaceindex == 1) {
			/* MAC0 enabled, only init radia B.   */
			true_bpath = true;
		}
	}

	for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {
		/* Mac1 use PHY0 write */
		if (mac1_initradioa_first) {
			if (rfpath == RF90_PATH_A) {
				rtlhal->during_mac1init_radioa = true;
				need_pwrdown_radioa = true;
			} else if (rfpath == RF90_PATH_B) {
				rtlhal->during_mac1init_radioa = false;
				mac1_initradioa_first = false;
				rfpath = RF90_PATH_A;
				true_bpath = true;
				rtlphy->num_total_rfpath = 1;
			}
		} else if (mac0_initradiob_first) {
			/* Mac0 use PHY1 write */
			if (rfpath == RF90_PATH_A)
				rtlhal->during_mac0init_radiob = false;
			if (rfpath == RF90_PATH_B) {
				rtlhal->during_mac0init_radiob = true;
				mac0_initradiob_first = false;
				need_pwrdown_radiob = true;
				rfpath = RF90_PATH_A;
				true_bpath = true;
				rtlphy->num_total_rfpath = 1;
			}
		}
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
		/* Set bit number of Address and Data for RF register */
		/* Set 1 to 4 bits for 8255 */
		rtl_set_bbreg(hw, pphyreg->rfhssi_para2,
			      B3WIREADDRESSLENGTH, 0x0);
		udelay(1);
		/* Set 0 to 12  bits for 8255 */
		rtl_set_bbreg(hw, pphyreg->rfhssi_para2, B3WIREDATALENGTH, 0x0);
		udelay(1);
		switch (rfpath) {
		case RF90_PATH_A:
			if (true_bpath)
				rtstatus = rtl92d_phy_config_rf_with_headerfile(
						hw, radiob_txt,
						(enum radio_path)rfpath);
			else
				rtstatus = rtl92d_phy_config_rf_with_headerfile(
					     hw, radioa_txt,
					     (enum radio_path)rfpath);
			break;
		case RF90_PATH_B:
			rtstatus =
			    rtl92d_phy_config_rf_with_headerfile(hw, radiob_txt,
						(enum radio_path) rfpath);
			break;
		case RF90_PATH_C:
			break;
		case RF90_PATH_D:
			break;
		}
		switch (rfpath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			rtl_set_bbreg(hw, pphyreg->rfintfs, BRFSI_RFENV,
				      u4_regvalue);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			rtl_set_bbreg(hw, pphyreg->rfintfs, BRFSI_RFENV << 16,
				      u4_regvalue);
			break;
		}
		if (!rtstatus) {
			RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
				 "Radio[%d] Fail!!\n", rfpath);
			goto phy_rf_cfg_fail;
		}

	}

	/* check MAC0 enable or not again, if enabled,
	 * not power down radio A. */
	/* check MAC1 enable or not again, if enabled,
	 * not power down radio B. */
	if (need_pwrdown_radioa)
		rtl92d_phy_powerdown_anotherphy(hw, false);
	else if (need_pwrdown_radiob)
		rtl92d_phy_powerdown_anotherphy(hw, true);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "<---\n");
	return rtstatus;

phy_rf_cfg_fail:
	return rtstatus;
}