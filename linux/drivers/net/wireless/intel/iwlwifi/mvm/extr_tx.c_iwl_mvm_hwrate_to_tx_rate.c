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
typedef  int u32 ;
struct ieee80211_tx_rate {int idx; int /*<<< orphan*/  flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_RC_160_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_GREEN_FIELD ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_VHT_MCS ; 
 int RATE_HT_MCS_GF_MSK ; 
 int RATE_HT_MCS_INDEX_MSK ; 
#define  RATE_MCS_CHAN_WIDTH_160 131 
#define  RATE_MCS_CHAN_WIDTH_20 130 
#define  RATE_MCS_CHAN_WIDTH_40 129 
#define  RATE_MCS_CHAN_WIDTH_80 128 
 int RATE_MCS_CHAN_WIDTH_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int RATE_MCS_VHT_MSK ; 
 int RATE_VHT_MCS_NSS_MSK ; 
 int RATE_VHT_MCS_NSS_POS ; 
 int RATE_VHT_MCS_RATE_CODE_MSK ; 
 int /*<<< orphan*/  ieee80211_rate_set_vht (struct ieee80211_tx_rate*,int,int) ; 
 int iwl_mvm_legacy_rate_to_mac80211_idx (int,int) ; 

void iwl_mvm_hwrate_to_tx_rate(u32 rate_n_flags,
			       enum nl80211_band band,
			       struct ieee80211_tx_rate *r)
{
	if (rate_n_flags & RATE_HT_MCS_GF_MSK)
		r->flags |= IEEE80211_TX_RC_GREEN_FIELD;
	switch (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) {
	case RATE_MCS_CHAN_WIDTH_20:
		break;
	case RATE_MCS_CHAN_WIDTH_40:
		r->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		break;
	case RATE_MCS_CHAN_WIDTH_80:
		r->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
		break;
	case RATE_MCS_CHAN_WIDTH_160:
		r->flags |= IEEE80211_TX_RC_160_MHZ_WIDTH;
		break;
	}
	if (rate_n_flags & RATE_MCS_SGI_MSK)
		r->flags |= IEEE80211_TX_RC_SHORT_GI;
	if (rate_n_flags & RATE_MCS_HT_MSK) {
		r->flags |= IEEE80211_TX_RC_MCS;
		r->idx = rate_n_flags & RATE_HT_MCS_INDEX_MSK;
	} else if (rate_n_flags & RATE_MCS_VHT_MSK) {
		ieee80211_rate_set_vht(
			r, rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK,
			((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
						RATE_VHT_MCS_NSS_POS) + 1);
		r->flags |= IEEE80211_TX_RC_VHT_MCS;
	} else {
		r->idx = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							     band);
	}
}