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
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int** txpwrlevel_cck; int** txpwrlevel_ht40_1s; int** txpwr_legacyhtdiff; int** txpwr_ht20diff; int** txpwr_ht40diff; int eeprom_regulatory; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int DESC92C_RATE54M ; 
 int DESC92C_RATE6M ; 
 int DESC92C_RATEMCS0 ; 
 int DESC92C_RATEMCS15 ; 
 int DESC92C_RATEMCS8 ; 
 int HT_CHANNEL_WIDTH_20 ; 
 int HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ IS_CCK_RATE (int /*<<< orphan*/ ) ; 
 int MAX_POWER_INDEX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t TX_1S ; 
 size_t TX_2S ; 
 int _rtl92ee_get_txpower_by_rate (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl92ee_get_txpower_index(struct ieee80211_hw *hw,
				     enum radio_path rfpath, u8 rate,
				     u8 bw, u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 index = (channel - 1);
	u8 tx_power = 0;
	u8 diff = 0;

	if (channel < 1 || channel > 14) {
		index = 0;
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_DMESG,
			 "Illegal channel!!\n");
	}

	if (IS_CCK_RATE((s8)rate))
		tx_power = rtlefuse->txpwrlevel_cck[rfpath][index];
	else if (DESC92C_RATE6M <= rate)
		tx_power = rtlefuse->txpwrlevel_ht40_1s[rfpath][index];

	/* OFDM-1T*/
	if (DESC92C_RATE6M <= rate && rate <= DESC92C_RATE54M &&
	    !IS_CCK_RATE((s8)rate))
		tx_power += rtlefuse->txpwr_legacyhtdiff[rfpath][TX_1S];

	/* BW20-1S, BW20-2S */
	if (bw == HT_CHANNEL_WIDTH_20) {
		if (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			tx_power += rtlefuse->txpwr_ht20diff[rfpath][TX_1S];
		if (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			tx_power += rtlefuse->txpwr_ht20diff[rfpath][TX_2S];
	} else if (bw == HT_CHANNEL_WIDTH_20_40) {/* BW40-1S, BW40-2S */
		if (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			tx_power += rtlefuse->txpwr_ht40diff[rfpath][TX_1S];
		if (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			tx_power += rtlefuse->txpwr_ht40diff[rfpath][TX_2S];
	}

	if (rtlefuse->eeprom_regulatory != 2)
		diff = _rtl92ee_get_txpower_by_rate(hw, BAND_ON_2_4G,
						    rfpath, rate);

	tx_power += diff;

	if (tx_power > MAX_POWER_INDEX)
		tx_power = MAX_POWER_INDEX;

	return tx_power;
}