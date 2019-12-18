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
typedef  int u8 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int** eeprom_chnlarea_txpwr_cck; int** eeprom_chnlarea_txpwr_ht40_1s; int** eprom_chnl_txpwr_ht40_2sdf; int** txpwrlevel_cck; int** txpwrlevel_ht40_1s; scalar_t__** txpwrlevel_ht40_2s; int* eeprom_pwrlimit_ht40; int* eeprom_pwrlimit_ht20; int** pwrgroup_ht20; int** pwrgroup_ht40; int** txpwr_ht20diff; int** txpwr_legacyhtdiff; int legacy_ht_txpowerdiff; int eeprom_regulatory; int* eeprom_tssi; int eeprom_thermalmeter; int apk_thermalmeterignore; int* thermalmeter; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EEPROM_DEFAULT_HT20_DIFF ; 
 int EEPROM_DEFAULT_HT40_2SDIFF ; 
 int EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF ; 
 int EEPROM_DEFAULT_THERMALMETER ; 
 void* EEPROM_DEFAULT_TSSI ; 
 void* EEPROM_DEFAULT_TXPOWERLEVEL ; 
 size_t EEPROM_THERMAL_METER ; 
 size_t EEPROM_TSSI_A ; 
 size_t EEPROM_TSSI_B ; 
 int EEPROM_TXPOWERCCK ; 
 int EEPROM_TXPOWERHT20DIFF ; 
 int EEPROM_TXPOWERHT40_1S ; 
 int EEPROM_TXPOWERHT40_2SDIFF ; 
 int EEPROM_TXPOWER_OFDMDIFF ; 
 int EEPROM_TXPWR_GROUP ; 
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_EEPROM ; 
 int /*<<< orphan*/  INIT_TXPOWER ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 size_t RF_OPTION1 ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int rtl92c_get_chnl_group (int) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92cu_read_txpower_info_from_hwpg(struct ieee80211_hw *hw,
						 bool autoload_fail,
						 u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 rf_path, index, tempval;
	u16 i;

	for (rf_path = 0; rf_path < 2; rf_path++) {
		for (i = 0; i < 3; i++) {
			if (!autoload_fail) {
				rtlefuse->
				    eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERCCK + rf_path * 3 + i];
				rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERHT40_1S + rf_path * 3 +
					   i];
			} else {
				rtlefuse->
				    eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
				rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
			}
		}
	}
	for (i = 0; i < 3; i++) {
		if (!autoload_fail)
			tempval = hwinfo[EEPROM_TXPOWERHT40_2SDIFF + i];
		else
			tempval = EEPROM_DEFAULT_HT40_2SDIFF;
		rtlefuse->eprom_chnl_txpwr_ht40_2sdf[RF90_PATH_A][i] =
		    (tempval & 0xf);
		rtlefuse->eprom_chnl_txpwr_ht40_2sdf[RF90_PATH_B][i] =
		    ((tempval & 0xf0) >> 4);
	}
	for (rf_path = 0; rf_path < 2; rf_path++)
		for (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM CCK Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eeprom_chnlarea_txpwr_cck[rf_path][i]);
	for (rf_path = 0; rf_path < 2; rf_path++)
		for (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 1S Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eeprom_chnlarea_txpwr_ht40_1s[rf_path][i]);
	for (rf_path = 0; rf_path < 2; rf_path++)
		for (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 2S Diff Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eprom_chnl_txpwr_ht40_2sdf[rf_path][i]);
	for (rf_path = 0; rf_path < 2; rf_path++) {
		for (i = 0; i < 14; i++) {
			index = rtl92c_get_chnl_group((u8)i);
			rtlefuse->txpwrlevel_cck[rf_path][i] =
			    rtlefuse->eeprom_chnlarea_txpwr_cck[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
			    rtlefuse->
			    eeprom_chnlarea_txpwr_ht40_1s[rf_path][index];
			if ((rtlefuse->
			     eeprom_chnlarea_txpwr_ht40_1s[rf_path][index] -
			     rtlefuse->
			     eprom_chnl_txpwr_ht40_2sdf[rf_path][index])
			    > 0) {
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] =
				    rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path]
				    [index] - rtlefuse->
				    eprom_chnl_txpwr_ht40_2sdf[rf_path]
				    [index];
			} else {
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] = 0;
			}
		}
		for (i = 0; i < 14; i++) {
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF(%d)-Ch(%d) [CCK / HT40_1S / HT40_2S] = [0x%x / 0x%x / 0x%x]\n", rf_path, i,
				rtlefuse->txpwrlevel_cck[rf_path][i],
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i],
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i]);
		}
	}
	for (i = 0; i < 3; i++) {
		if (!autoload_fail) {
			rtlefuse->eeprom_pwrlimit_ht40[i] =
			    hwinfo[EEPROM_TXPWR_GROUP + i];
			rtlefuse->eeprom_pwrlimit_ht20[i] =
			    hwinfo[EEPROM_TXPWR_GROUP + 3 + i];
		} else {
			rtlefuse->eeprom_pwrlimit_ht40[i] = 0;
			rtlefuse->eeprom_pwrlimit_ht20[i] = 0;
		}
	}
	for (rf_path = 0; rf_path < 2; rf_path++) {
		for (i = 0; i < 14; i++) {
			index = rtl92c_get_chnl_group((u8)i);
			if (rf_path == RF90_PATH_A) {
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				    (rtlefuse->eeprom_pwrlimit_ht20[index]
				     & 0xf);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				    (rtlefuse->eeprom_pwrlimit_ht40[index]
				     & 0xf);
			} else if (rf_path == RF90_PATH_B) {
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				    ((rtlefuse->eeprom_pwrlimit_ht20[index]
				      & 0xf0) >> 4);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				    ((rtlefuse->eeprom_pwrlimit_ht40[index]
				      & 0xf0) >> 4);
			}
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht20[%d] = 0x%x\n",
				rf_path, i,
				rtlefuse->pwrgroup_ht20[rf_path][i]);
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht40[%d] = 0x%x\n",
				rf_path, i,
				rtlefuse->pwrgroup_ht40[rf_path][i]);
		}
	}
	for (i = 0; i < 14; i++) {
		index = rtl92c_get_chnl_group((u8)i);
		if (!autoload_fail)
			tempval = hwinfo[EEPROM_TXPOWERHT20DIFF + index];
		else
			tempval = EEPROM_DEFAULT_HT20_DIFF;
		rtlefuse->txpwr_ht20diff[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_ht20diff[RF90_PATH_B][i] =
		    ((tempval >> 4) & 0xF);
		if (rtlefuse->txpwr_ht20diff[RF90_PATH_A][i] & BIT(3))
			rtlefuse->txpwr_ht20diff[RF90_PATH_A][i] |= 0xF0;
		if (rtlefuse->txpwr_ht20diff[RF90_PATH_B][i] & BIT(3))
			rtlefuse->txpwr_ht20diff[RF90_PATH_B][i] |= 0xF0;
		index = rtl92c_get_chnl_group((u8)i);
		if (!autoload_fail)
			tempval = hwinfo[EEPROM_TXPOWER_OFDMDIFF + index];
		else
			tempval = EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;
		rtlefuse->txpwr_legacyhtdiff[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_legacyhtdiff[RF90_PATH_B][i] =
		    ((tempval >> 4) & 0xF);
	}
	rtlefuse->legacy_ht_txpowerdiff =
	    rtlefuse->txpwr_legacyhtdiff[RF90_PATH_A][7];
	for (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_ht20diff[RF90_PATH_A][i]);
	for (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Legacy to Ht40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_legacyhtdiff[RF90_PATH_A][i]);
	for (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_ht20diff[RF90_PATH_B][i]);
	for (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Legacy to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_legacyhtdiff[RF90_PATH_B][i]);
	if (!autoload_fail)
		rtlefuse->eeprom_regulatory = (hwinfo[RF_OPTION1] & 0x7);
	else
		rtlefuse->eeprom_regulatory = 0;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
	if (!autoload_fail) {
		rtlefuse->eeprom_tssi[RF90_PATH_A] = hwinfo[EEPROM_TSSI_A];
		rtlefuse->eeprom_tssi[RF90_PATH_B] = hwinfo[EEPROM_TSSI_B];
	} else {
		rtlefuse->eeprom_tssi[RF90_PATH_A] = EEPROM_DEFAULT_TSSI;
		rtlefuse->eeprom_tssi[RF90_PATH_B] = EEPROM_DEFAULT_TSSI;
	}
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"TSSI_A = 0x%x, TSSI_B = 0x%x\n",
		rtlefuse->eeprom_tssi[RF90_PATH_A],
		rtlefuse->eeprom_tssi[RF90_PATH_B]);
	if (!autoload_fail)
		tempval = hwinfo[EEPROM_THERMAL_METER];
	else
		tempval = EEPROM_DEFAULT_THERMALMETER;
	rtlefuse->eeprom_thermalmeter = (tempval & 0x1f);
	if (rtlefuse->eeprom_thermalmeter < 0x06 ||
	    rtlefuse->eeprom_thermalmeter > 0x1c)
		rtlefuse->eeprom_thermalmeter = 0x12;
	if (rtlefuse->eeprom_thermalmeter == 0x1f || autoload_fail)
		rtlefuse->apk_thermalmeterignore = true;
	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);
}