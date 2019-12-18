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
typedef  int u8 ;
typedef  size_t u32 ;
struct txpower_info {int** ht40_1sindex; int** ht40_2sindexdiff; int /*<<< orphan*/ ** ht40maxoffset; int /*<<< orphan*/ ** ht20maxoffset; int /*<<< orphan*/ ** ofdmindexdiff; int /*<<< orphan*/ ** ht20indexdiff; int /*<<< orphan*/ ** cck_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct rtl_efuse {int eeprom_regulatory; int eeprom_thermalmeter; int crystalcap; int txpwr_fromeprom; int* internal_pa_5g; int eeprom_c9; int eeprom_cc; int* thermalmeter; int delta_iqk; int delta_lck; int** txpwrlevel_ht40_1s; int** txpwrlevel_ht40_2s; int /*<<< orphan*/ ** pwrgroup_ht40; int /*<<< orphan*/ ** pwrgroup_ht20; int /*<<< orphan*/ ** txpwr_legacyhtdiff; int /*<<< orphan*/ ** txpwr_ht20diff; int /*<<< orphan*/ ** txpwrlevel_cck; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t CHANNEL_MAX_NUMBER ; 
 size_t CHANNEL_MAX_NUMBER_2G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  COMP_INTR ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_DEFAULT_CRYSTALCAP ; 
 int EEPROM_DEFAULT_THERMALMETER ; 
 size_t EEPROM_IQK_DELTA ; 
 size_t EEPROM_LCK_DELTA ; 
 size_t EEPROM_RF_OPT1 ; 
 size_t EEPROM_RF_OPT6 ; 
 size_t EEPROM_RF_OPT7 ; 
 size_t EEPROM_THERMAL_METER ; 
 size_t EEPROM_TSSI_A_5G ; 
 size_t EEPROM_TSSI_B_5G ; 
 size_t EEPROM_XTAL_K ; 
 scalar_t__ IS_92D_D_CUT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_92D_E_CUT (int /*<<< orphan*/ ) ; 
 size_t RF6052_MAX_PATH ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  _rtl92de_readpowervalue_fromprom (struct txpower_info*,int*,int) ; 
 size_t rtl92d_get_chnlgroup_fromarray (int) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92de_read_txpower_info(struct ieee80211_hw *hw,
				       bool autoload_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct txpower_info pwrinfo;
	u8 tempval[2], i, pwr, diff;
	u32 ch, rfpath, group;

	_rtl92de_readpowervalue_fromprom(&pwrinfo, hwinfo, autoload_fail);
	if (!autoload_fail) {
		/* bit0~2 */
		rtlefuse->eeprom_regulatory = (hwinfo[EEPROM_RF_OPT1] & 0x7);
		rtlefuse->eeprom_thermalmeter =
			 hwinfo[EEPROM_THERMAL_METER] & 0x1f;
		rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_K];
		tempval[0] = hwinfo[EEPROM_IQK_DELTA] & 0x03;
		tempval[1] = (hwinfo[EEPROM_LCK_DELTA] & 0x0C) >> 2;
		rtlefuse->txpwr_fromeprom = true;
		if (IS_92D_D_CUT(rtlpriv->rtlhal.version) ||
		    IS_92D_E_CUT(rtlpriv->rtlhal.version)) {
			rtlefuse->internal_pa_5g[0] =
				!((hwinfo[EEPROM_TSSI_A_5G] & BIT(6)) >> 6);
			rtlefuse->internal_pa_5g[1] =
				!((hwinfo[EEPROM_TSSI_B_5G] & BIT(6)) >> 6);
			RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG,
				 "Is D cut,Internal PA0 %d Internal PA1 %d\n",
				 rtlefuse->internal_pa_5g[0],
				 rtlefuse->internal_pa_5g[1]);
		}
		rtlefuse->eeprom_c9 = hwinfo[EEPROM_RF_OPT6];
		rtlefuse->eeprom_cc = hwinfo[EEPROM_RF_OPT7];
	} else {
		rtlefuse->eeprom_regulatory = 0;
		rtlefuse->eeprom_thermalmeter = EEPROM_DEFAULT_THERMALMETER;
		rtlefuse->crystalcap = EEPROM_DEFAULT_CRYSTALCAP;
		tempval[0] = tempval[1] = 3;
	}

	/* Use default value to fill parameters if
	 * efuse is not filled on some place. */

	/* ThermalMeter from EEPROM */
	if (rtlefuse->eeprom_thermalmeter < 0x06 ||
	    rtlefuse->eeprom_thermalmeter > 0x1c)
		rtlefuse->eeprom_thermalmeter = 0x12;
	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;

	/* check XTAL_K */
	if (rtlefuse->crystalcap == 0xFF)
		rtlefuse->crystalcap = 0;
	if (rtlefuse->eeprom_regulatory > 3)
		rtlefuse->eeprom_regulatory = 0;

	for (i = 0; i < 2; i++) {
		switch (tempval[i]) {
		case 0:
			tempval[i] = 5;
			break;
		case 1:
			tempval[i] = 4;
			break;
		case 2:
			tempval[i] = 3;
			break;
		case 3:
		default:
			tempval[i] = 0;
			break;
		}
	}

	rtlefuse->delta_iqk = tempval[0];
	if (tempval[1] > 0)
		rtlefuse->delta_lck = tempval[1] - 1;
	if (rtlefuse->eeprom_c9 == 0xFF)
		rtlefuse->eeprom_c9 = 0x00;
	RT_TRACE(rtlpriv, COMP_INTR, DBG_LOUD,
		 "EEPROMRegulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
	RT_TRACE(rtlpriv, COMP_INTR, DBG_LOUD,
		 "ThermalMeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);
	RT_TRACE(rtlpriv, COMP_INTR, DBG_LOUD,
		 "CrystalCap = 0x%x\n", rtlefuse->crystalcap);
	RT_TRACE(rtlpriv, COMP_INTR, DBG_LOUD,
		 "Delta_IQK = 0x%x Delta_LCK = 0x%x\n",
		 rtlefuse->delta_iqk, rtlefuse->delta_lck);

	for (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) {
		for (ch = 0; ch < CHANNEL_MAX_NUMBER; ch++) {
			group = rtl92d_get_chnlgroup_fromarray((u8) ch);
			if (ch < CHANNEL_MAX_NUMBER_2G)
				rtlefuse->txpwrlevel_cck[rfpath][ch] =
				    pwrinfo.cck_index[rfpath][group];
			rtlefuse->txpwrlevel_ht40_1s[rfpath][ch] =
				    pwrinfo.ht40_1sindex[rfpath][group];
			rtlefuse->txpwr_ht20diff[rfpath][ch] =
				    pwrinfo.ht20indexdiff[rfpath][group];
			rtlefuse->txpwr_legacyhtdiff[rfpath][ch] =
				    pwrinfo.ofdmindexdiff[rfpath][group];
			rtlefuse->pwrgroup_ht20[rfpath][ch] =
				    pwrinfo.ht20maxoffset[rfpath][group];
			rtlefuse->pwrgroup_ht40[rfpath][ch] =
				    pwrinfo.ht40maxoffset[rfpath][group];
			pwr = pwrinfo.ht40_1sindex[rfpath][group];
			diff = pwrinfo.ht40_2sindexdiff[rfpath][group];
			rtlefuse->txpwrlevel_ht40_2s[rfpath][ch] =
				    (pwr > diff) ? (pwr - diff) : 0;
		}
	}
}