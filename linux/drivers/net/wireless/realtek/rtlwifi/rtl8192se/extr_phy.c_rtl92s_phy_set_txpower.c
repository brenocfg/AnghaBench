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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int /*<<< orphan*/  txpwr_fromeprom; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92s_phy_ccxpower_indexcheck (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92s_phy_get_txpower_index (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl92s_phy_rf6052_set_ccktxpower (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92s_phy_rf6052_set_ofdmtxpower (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92s_phy_set_txpower(struct ieee80211_hw *hw, u8	channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	/* [0]:RF-A, [1]:RF-B */
	u8 cckpowerlevel[2], ofdmpowerlevel[2];

	if (!rtlefuse->txpwr_fromeprom)
		return;

	/* Mainly we use RF-A Tx Power to write the Tx Power registers,
	 * but the RF-B Tx Power must be calculated by the antenna diff.
	 * So we have to rewrite Antenna gain offset register here.
	 * Please refer to BB register 0x80c
	 * 1. For CCK.
	 * 2. For OFDM 1T or 2T */
	_rtl92s_phy_get_txpower_index(hw, channel, &cckpowerlevel[0],
			&ofdmpowerlevel[0]);

	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
		 "Channel-%d, cckPowerLevel (A / B) = 0x%x / 0x%x, ofdmPowerLevel (A / B) = 0x%x / 0x%x\n",
		 channel, cckpowerlevel[0], cckpowerlevel[1],
		 ofdmpowerlevel[0], ofdmpowerlevel[1]);

	_rtl92s_phy_ccxpower_indexcheck(hw, channel, &cckpowerlevel[0],
			&ofdmpowerlevel[0]);

	rtl92s_phy_rf6052_set_ccktxpower(hw, cckpowerlevel[0]);
	rtl92s_phy_rf6052_set_ofdmtxpower(hw, &ofdmpowerlevel[0], channel);

}