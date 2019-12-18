#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct rtl_sta_info {scalar_t__ wireless_mode; } ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {scalar_t__ opmode; scalar_t__ bw_40; scalar_t__ bw_80; } ;
struct ieee80211_tx_rate_control {scalar_t__ short_preamble; } ;
struct ieee80211_tx_rate {int count; int idx; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int cap; scalar_t__ vht_supported; } ;
struct TYPE_3__ {int cap; scalar_t__ ht_supported; } ;
struct ieee80211_sta {TYPE_2__ vht_cap; TYPE_1__ ht_cap; scalar_t__ drv_priv; } ;
typedef  int s8 ;

/* Variables and functions */
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_VHT_MCS ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ WIRELESS_MODE_AC_24G ; 
 scalar_t__ WIRELESS_MODE_AC_5G ; 
 scalar_t__ WIRELESS_MODE_AC_ONLY ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 scalar_t__ WIRELESS_MODE_N_5G ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 

__attribute__((used)) static void _rtl_rc_rate_set_series(struct rtl_priv *rtlpriv,
				    struct ieee80211_sta *sta,
				    struct ieee80211_tx_rate *rate,
				    struct ieee80211_tx_rate_control *txrc,
				    u8 tries, s8 rix, int rtsctsenable,
				    bool not_data)
{
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	struct rtl_sta_info *sta_entry = NULL;
	u16 wireless_mode = 0;
	u8 sgi_20 = 0, sgi_40 = 0, sgi_80 = 0;

	if (sta) {
		sgi_20 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20;
		sgi_40 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40;
		sgi_80 = sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80;
		sta_entry = (struct rtl_sta_info *)sta->drv_priv;
		wireless_mode = sta_entry->wireless_mode;
	}
	rate->count = tries;
	rate->idx = rix >= 0x00 ? rix : 0x00;

	if (!not_data) {
		if (txrc->short_preamble)
			rate->flags |= IEEE80211_TX_RC_USE_SHORT_PREAMBLE;
		if (mac->opmode == NL80211_IFTYPE_AP ||
			mac->opmode == NL80211_IFTYPE_ADHOC) {
			if (sta && (sta->ht_cap.cap &
				    IEEE80211_HT_CAP_SUP_WIDTH_20_40))
				rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
			if (sta && sta->vht_cap.vht_supported)
				rate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
		} else {
			if (mac->bw_80)
				rate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
			else if (mac->bw_40)
				rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		}

		if (sgi_20 || sgi_40 || sgi_80)
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;
		if (sta && sta->ht_cap.ht_supported &&
		    (wireless_mode == WIRELESS_MODE_N_5G ||
		     wireless_mode == WIRELESS_MODE_N_24G))
			rate->flags |= IEEE80211_TX_RC_MCS;
		if (sta && sta->vht_cap.vht_supported &&
		    (wireless_mode == WIRELESS_MODE_AC_5G ||
		     wireless_mode == WIRELESS_MODE_AC_24G ||
		     wireless_mode == WIRELESS_MODE_AC_ONLY))
			rate->flags |= IEEE80211_TX_RC_VHT_MCS;
	}
}