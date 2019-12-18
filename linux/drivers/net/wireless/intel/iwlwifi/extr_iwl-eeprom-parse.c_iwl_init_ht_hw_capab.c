#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct iwl_trans {TYPE_1__* trans_cfg; struct iwl_cfg* cfg; } ;
struct iwl_nvm_data {scalar_t__ sku_cap_mimo_disabled; int /*<<< orphan*/  sku_cap_11n_enable; } ;
struct iwl_cfg {TYPE_2__* ht_params; int /*<<< orphan*/  max_ht_ampdu_exponent; scalar_t__ rx_with_siso_diversity; } ;
struct TYPE_7__ {int* rx_mask; int tx_params; int /*<<< orphan*/  rx_highest; } ;
struct ieee80211_sta_ht_cap {int ht_supported; int cap; TYPE_3__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_8__ {int disable_11n; scalar_t__ amsdu_size; } ;
struct TYPE_6__ {int ht40_bands; scalar_t__ ht_greenfield_support; scalar_t__ ldpc; scalar_t__ stbc; } ;
struct TYPE_5__ {scalar_t__ mq_rx_supported; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_GRN_FLD ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int IEEE80211_HT_MCS_RX_HIGHEST_MASK ; 
 int IEEE80211_HT_MCS_TX_DEFINED ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_4 ; 
 scalar_t__ IWL_AMSDU_8K ; 
 scalar_t__ IWL_AMSDU_DEF ; 
 int IWL_DISABLE_HT_ALL ; 
 int MAX_BIT_RATE_20_MHZ ; 
 int MAX_BIT_RATE_40_MHZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int hweight8 (int) ; 
 TYPE_4__ iwlwifi_mod_params ; 

void iwl_init_ht_hw_capab(struct iwl_trans *trans,
			  struct iwl_nvm_data *data,
			  struct ieee80211_sta_ht_cap *ht_info,
			  enum nl80211_band band,
			  u8 tx_chains, u8 rx_chains)
{
	const struct iwl_cfg *cfg = trans->cfg;
	int max_bit_rate = 0;

	tx_chains = hweight8(tx_chains);
	if (cfg->rx_with_siso_diversity)
		rx_chains = 1;
	else
		rx_chains = hweight8(rx_chains);

	if (!(data->sku_cap_11n_enable) ||
	    (iwlwifi_mod_params.disable_11n & IWL_DISABLE_HT_ALL) ||
	    !cfg->ht_params) {
		ht_info->ht_supported = false;
		return;
	}

	if (data->sku_cap_mimo_disabled)
		rx_chains = 1;

	ht_info->ht_supported = true;
	ht_info->cap = IEEE80211_HT_CAP_DSSSCCK40;

	if (cfg->ht_params->stbc) {
		ht_info->cap |= (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);

		if (tx_chains > 1)
			ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
	}

	if (cfg->ht_params->ldpc)
		ht_info->cap |= IEEE80211_HT_CAP_LDPC_CODING;

	if ((trans->trans_cfg->mq_rx_supported &&
	     iwlwifi_mod_params.amsdu_size == IWL_AMSDU_DEF) ||
	     iwlwifi_mod_params.amsdu_size >= IWL_AMSDU_8K)
		ht_info->cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	ht_info->ampdu_factor = cfg->max_ht_ampdu_exponent;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_4;

	ht_info->mcs.rx_mask[0] = 0xFF;
	if (rx_chains >= 2)
		ht_info->mcs.rx_mask[1] = 0xFF;
	if (rx_chains >= 3)
		ht_info->mcs.rx_mask[2] = 0xFF;

	if (cfg->ht_params->ht_greenfield_support)
		ht_info->cap |= IEEE80211_HT_CAP_GRN_FLD;
	ht_info->cap |= IEEE80211_HT_CAP_SGI_20;

	max_bit_rate = MAX_BIT_RATE_20_MHZ;

	if (cfg->ht_params->ht40_bands & BIT(band)) {
		ht_info->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		ht_info->cap |= IEEE80211_HT_CAP_SGI_40;
		max_bit_rate = MAX_BIT_RATE_40_MHZ;
	}

	/* Highest supported Rx data rate */
	max_bit_rate *= rx_chains;
	WARN_ON(max_bit_rate & ~IEEE80211_HT_MCS_RX_HIGHEST_MASK);
	ht_info->mcs.rx_highest = cpu_to_le16(max_bit_rate);

	/* Tx MCS capabilities */
	ht_info->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	if (tx_chains != rx_chains) {
		ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		ht_info->mcs.tx_params |= ((tx_chains - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);
	}
}