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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ dynamic_txhighpower_lvl; } ;
struct rtl_phy {int** mcs_offset; } ;
struct rtl_priv {TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ mode; scalar_t__ act_scanning; } ;
struct rtl_efuse {scalar_t__ eeprom_regulatory; scalar_t__ external_pa; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPHY ; 
 int MASKBYTE0 ; 
 int MASKBYTE1 ; 
 int /*<<< orphan*/  PHY_TXPWR ; 
 size_t RF6052_MAX_TX_PWR ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTXAGC_A_CCK1_MCS32 ; 
 int /*<<< orphan*/  RTXAGC_B_CCK11_A_CCK2_11 ; 
 int /*<<< orphan*/  RTXAGC_B_CCK1_55_MCS32 ; 
 scalar_t__ TXHIGHPWRLEVEL_LEVEL1 ; 
 scalar_t__ TXHIGHPWRLEVEL_LEVEL2 ; 
 scalar_t__ WIRELESS_MODE_B ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

void rtl92cu_phy_rf6052_set_cck_txpower(struct ieee80211_hw *hw,
					u8 *ppowerlevel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 tx_agc[2] = { 0, 0 }, tmpval = 0;
	u8 idx1, idx2;
	u8 *ptr;

	if (mac->act_scanning) {
		tx_agc[RF90_PATH_A] = 0x3f3f3f3f;
		tx_agc[RF90_PATH_B] = 0x3f3f3f3f;
		for (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) {
			tx_agc[idx1] = ppowerlevel[idx1] |
			    (ppowerlevel[idx1] << 8) |
			    (ppowerlevel[idx1] << 16) |
			    (ppowerlevel[idx1] << 24);
			if (tx_agc[idx1] > 0x20 && rtlefuse->external_pa)
				tx_agc[idx1] = 0x20;
		}
	} else {
		if (rtlpriv->dm.dynamic_txhighpower_lvl ==
		    TXHIGHPWRLEVEL_LEVEL1) {
			tx_agc[RF90_PATH_A] = 0x10101010;
			tx_agc[RF90_PATH_B] = 0x10101010;
		} else if (rtlpriv->dm.dynamic_txhighpower_lvl ==
			   TXHIGHPWRLEVEL_LEVEL2) {
			tx_agc[RF90_PATH_A] = 0x00000000;
			tx_agc[RF90_PATH_B] = 0x00000000;
		} else {
			for (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) {
				tx_agc[idx1] = ppowerlevel[idx1] |
				    (ppowerlevel[idx1] << 8) |
				    (ppowerlevel[idx1] << 16) |
				    (ppowerlevel[idx1] << 24);
			}
			if (rtlefuse->eeprom_regulatory == 0) {
				tmpval = (rtlphy->mcs_offset[0][6]) +
					(rtlphy->mcs_offset[0][7] <<  8);
				tx_agc[RF90_PATH_A] += tmpval;
				tmpval = (rtlphy->mcs_offset[0][14]) +
					(rtlphy->mcs_offset[0][15] << 24);
				tx_agc[RF90_PATH_B] += tmpval;
			}
		}
	}
	for (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) {
		ptr = (u8 *) (&(tx_agc[idx1]));
		for (idx2 = 0; idx2 < 4; idx2++) {
			if (*ptr > RF6052_MAX_TX_PWR)
				*ptr = RF6052_MAX_TX_PWR;
			ptr++;
		}
	}
	tmpval = tx_agc[RF90_PATH_A] & 0xff;
	rtl_set_bbreg(hw, RTXAGC_A_CCK1_MCS32, MASKBYTE1, tmpval);

	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 1M (rf-A) = 0x%x (reg 0x%x)\n",
		tmpval, RTXAGC_A_CCK1_MCS32);

	tmpval = tx_agc[RF90_PATH_A] >> 8;
	if (mac->mode == WIRELESS_MODE_B)
		tmpval = tmpval & 0xff00ffff;
	rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, 0xffffff00, tmpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 2~11M (rf-A) = 0x%x (reg 0x%x)\n",
		tmpval, RTXAGC_B_CCK11_A_CCK2_11);
	tmpval = tx_agc[RF90_PATH_B] >> 24;
	rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE0, tmpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 11M (rf-B) = 0x%x (reg 0x%x)\n",
		tmpval, RTXAGC_B_CCK11_A_CCK2_11);
	tmpval = tx_agc[RF90_PATH_B] & 0x00ffffff;
	rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, 0xffffff00, tmpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 1~5.5M (rf-B) = 0x%x (reg 0x%x)\n",
		tmpval, RTXAGC_B_CCK1_55_MCS32);
}