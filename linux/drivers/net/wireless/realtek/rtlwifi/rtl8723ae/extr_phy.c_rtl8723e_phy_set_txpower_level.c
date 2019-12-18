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
struct rtl_efuse {int txpwr_fromeprom; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8723e_ccxpower_index_check (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl8723e_get_txpower_index (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8723e_phy_rf6052_set_cck_txpower (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8723e_phy_rf6052_set_ofdm_txpower (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

void rtl8723e_phy_set_txpower_level(struct ieee80211_hw *hw, u8 channel)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 cckpowerlevel[2], ofdmpowerlevel[2];

	if (rtlefuse->txpwr_fromeprom == false)
		return;
	_rtl8723e_get_txpower_index(hw, channel,
				    &cckpowerlevel[0], &ofdmpowerlevel[0]);
	_rtl8723e_ccxpower_index_check(hw,
				       channel, &cckpowerlevel[0],
				       &ofdmpowerlevel[0]);
	rtl8723e_phy_rf6052_set_cck_txpower(hw, &cckpowerlevel[0]);
	rtl8723e_phy_rf6052_set_ofdm_txpower(hw, &ofdmpowerlevel[0], channel);
}