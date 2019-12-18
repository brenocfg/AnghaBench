#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {scalar_t__ current_bandtype; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_2__ rtlhal; } ;
struct ieee80211_tx_rate {int flags; int idx; } ;
struct TYPE_4__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_1__ status; } ;
struct ieee80211_rate {int hw_value; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {int* maps; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 size_t RTL_RC_HT_RATEMCS15 ; 
 size_t RTL_RC_OFDM_RATE6M ; 
 size_t RTL_RC_VHT_RATE_1SS_MCS9 ; 
 size_t RTL_RC_VHT_RATE_2SS_MCS9 ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (struct ieee80211_hw*,struct ieee80211_tx_info*) ; 
 int ieee80211_rate_get_vht_mcs (struct ieee80211_tx_rate*) ; 
 int ieee80211_rate_get_vht_nss (struct ieee80211_tx_rate*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl_get_tx_hw_rate(struct ieee80211_hw *hw,
			      struct ieee80211_tx_info *info)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ieee80211_tx_rate *r = &info->status.rates[0];
	struct ieee80211_rate *txrate;
	u8 hw_value = 0x0;

	if (r->flags & IEEE80211_TX_RC_MCS) {
		/* HT MCS0-15 */
		hw_value = rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS15] - 15 +
			   r->idx;
	} else if (r->flags & IEEE80211_TX_RC_VHT_MCS) {
		/* VHT MCS0-9, NSS */
		if (ieee80211_rate_get_vht_nss(r) == 2)
			hw_value = rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS9];
		else
			hw_value = rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS9];

		hw_value = hw_value - 9 + ieee80211_rate_get_vht_mcs(r);
	} else {
		/* legacy */
		txrate = ieee80211_get_tx_rate(hw, info);

		if (txrate)
			hw_value = txrate->hw_value;
	}

	/* check 5G band */
	if (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G &&
	    hw_value < rtlpriv->cfg->maps[RTL_RC_OFDM_RATE6M])
		hw_value = rtlpriv->cfg->maps[RTL_RC_OFDM_RATE6M];

	return hw_value;
}