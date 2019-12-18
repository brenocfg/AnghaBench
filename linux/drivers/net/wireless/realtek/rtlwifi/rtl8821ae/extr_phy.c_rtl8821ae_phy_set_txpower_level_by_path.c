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
struct rtl_phy {int num_total_rfpath; int /*<<< orphan*/  current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 int DESC_RATE11M ; 
 int DESC_RATE12M ; 
 int DESC_RATE18M ; 
 int DESC_RATE1M ; 
 int DESC_RATE24M ; 
 int DESC_RATE2M ; 
 int DESC_RATE36M ; 
 int DESC_RATE48M ; 
 int DESC_RATE54M ; 
 int DESC_RATE5_5M ; 
 int DESC_RATE6M ; 
 int DESC_RATE9M ; 
 int DESC_RATEMCS0 ; 
 int DESC_RATEMCS1 ; 
 int DESC_RATEMCS10 ; 
 int DESC_RATEMCS11 ; 
 int DESC_RATEMCS12 ; 
 int DESC_RATEMCS13 ; 
 int DESC_RATEMCS14 ; 
 int DESC_RATEMCS15 ; 
 int DESC_RATEMCS2 ; 
 int DESC_RATEMCS3 ; 
 int DESC_RATEMCS4 ; 
 int DESC_RATEMCS5 ; 
 int DESC_RATEMCS6 ; 
 int DESC_RATEMCS7 ; 
 int DESC_RATEMCS8 ; 
 int DESC_RATEMCS9 ; 
 int DESC_RATEVHT1SS_MCS0 ; 
 int DESC_RATEVHT1SS_MCS1 ; 
 int DESC_RATEVHT1SS_MCS2 ; 
 int DESC_RATEVHT1SS_MCS3 ; 
 int DESC_RATEVHT1SS_MCS4 ; 
 int DESC_RATEVHT1SS_MCS5 ; 
 int DESC_RATEVHT1SS_MCS6 ; 
 int DESC_RATEVHT1SS_MCS7 ; 
 int DESC_RATEVHT1SS_MCS8 ; 
 int DESC_RATEVHT1SS_MCS9 ; 
 int DESC_RATEVHT2SS_MCS0 ; 
 int DESC_RATEVHT2SS_MCS1 ; 
 int DESC_RATEVHT2SS_MCS2 ; 
 int DESC_RATEVHT2SS_MCS3 ; 
 int DESC_RATEVHT2SS_MCS4 ; 
 int DESC_RATEVHT2SS_MCS5 ; 
 int DESC_RATEVHT2SS_MCS6 ; 
 int DESC_RATEVHT2SS_MCS7 ; 
 int DESC_RATEVHT2SS_MCS8 ; 
 int DESC_RATEVHT2SS_MCS9 ; 
 int /*<<< orphan*/  _rtl8821ae_phy_set_txpower_level_by_path (struct ieee80211_hw*,int*,int,int,int) ; 
 int /*<<< orphan*/  _rtl8821ae_phy_txpower_training_by_path (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8821ae_phy_set_txpower_level_by_path(struct ieee80211_hw *hw,
					     u8 channel, u8 path)
{
	/* struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw)); */
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 cck_rates[]  = {DESC_RATE1M, DESC_RATE2M, DESC_RATE5_5M,
			      DESC_RATE11M};
	u8 sizes_of_cck_retes = 4;
	u8 ofdm_rates[]  = {DESC_RATE6M, DESC_RATE9M, DESC_RATE12M,
				DESC_RATE18M, DESC_RATE24M, DESC_RATE36M,
				DESC_RATE48M, DESC_RATE54M};
	u8 sizes_of_ofdm_retes = 8;
	u8 ht_rates_1t[]  = {DESC_RATEMCS0, DESC_RATEMCS1, DESC_RATEMCS2,
				DESC_RATEMCS3, DESC_RATEMCS4, DESC_RATEMCS5,
				DESC_RATEMCS6, DESC_RATEMCS7};
	u8 sizes_of_ht_retes_1t = 8;
	u8 ht_rates_2t[]  = {DESC_RATEMCS8, DESC_RATEMCS9,
				DESC_RATEMCS10, DESC_RATEMCS11,
				DESC_RATEMCS12, DESC_RATEMCS13,
				DESC_RATEMCS14, DESC_RATEMCS15};
	u8 sizes_of_ht_retes_2t = 8;
	u8 vht_rates_1t[]  = {DESC_RATEVHT1SS_MCS0, DESC_RATEVHT1SS_MCS1,
				DESC_RATEVHT1SS_MCS2, DESC_RATEVHT1SS_MCS3,
				DESC_RATEVHT1SS_MCS4, DESC_RATEVHT1SS_MCS5,
				DESC_RATEVHT1SS_MCS6, DESC_RATEVHT1SS_MCS7,
			     DESC_RATEVHT1SS_MCS8, DESC_RATEVHT1SS_MCS9};
	u8 vht_rates_2t[]  = {DESC_RATEVHT2SS_MCS0, DESC_RATEVHT2SS_MCS1,
				DESC_RATEVHT2SS_MCS2, DESC_RATEVHT2SS_MCS3,
				DESC_RATEVHT2SS_MCS4, DESC_RATEVHT2SS_MCS5,
				DESC_RATEVHT2SS_MCS6, DESC_RATEVHT2SS_MCS7,
				DESC_RATEVHT2SS_MCS8, DESC_RATEVHT2SS_MCS9};
	u8 sizes_of_vht_retes = 10;

	if (rtlhal->current_bandtype == BAND_ON_2_4G)
		_rtl8821ae_phy_set_txpower_level_by_path(hw, cck_rates, path, channel,
							 sizes_of_cck_retes);

	_rtl8821ae_phy_set_txpower_level_by_path(hw, ofdm_rates, path, channel,
						 sizes_of_ofdm_retes);
	_rtl8821ae_phy_set_txpower_level_by_path(hw, ht_rates_1t, path, channel,
						 sizes_of_ht_retes_1t);
	_rtl8821ae_phy_set_txpower_level_by_path(hw, vht_rates_1t, path, channel,
						 sizes_of_vht_retes);

	if (rtlphy->num_total_rfpath >= 2) {
		_rtl8821ae_phy_set_txpower_level_by_path(hw, ht_rates_2t, path,
							 channel,
							 sizes_of_ht_retes_2t);
		_rtl8821ae_phy_set_txpower_level_by_path(hw, vht_rates_2t, path,
							 channel,
							 sizes_of_vht_retes);
	}

	_rtl8821ae_phy_txpower_training_by_path(hw, rtlphy->current_chan_bw,
						channel, path);
}