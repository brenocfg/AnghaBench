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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_trans {TYPE_2__* trans_cfg; struct iwl_cfg* cfg; } ;
struct iwl_nvm_data {scalar_t__ sku_cap_mimo_disabled; scalar_t__ vht160_supported; } ;
struct iwl_cfg {scalar_t__ rx_with_siso_diversity; TYPE_1__* ht_params; scalar_t__ vht_mu_mimo_supported; scalar_t__ max_vht_ampdu_exponent; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_highest; int /*<<< orphan*/  rx_mcs_map; int /*<<< orphan*/  tx_mcs_map; } ;
struct ieee80211_sta_vht_cap {int vht_supported; int cap; TYPE_3__ vht_mcs; } ;
struct TYPE_8__ {int amsdu_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  mq_rx_supported; } ;
struct TYPE_5__ {scalar_t__ ldpc; } ;

/* Variables and functions */
 int IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT ; 
 unsigned int IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT ; 
 int IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 ; 
 int IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895 ; 
 int IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991 ; 
 int IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_1 ; 
 int IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN ; 
 int IEEE80211_VHT_CAP_SHORT_GI_160 ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 int IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ ; 
 int IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHT_CAP_TXSTBC ; 
 int IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN ; 
 int IEEE80211_VHT_EXT_NSS_BW_CAPABLE ; 
 unsigned int IEEE80211_VHT_MAX_AMPDU_1024K ; 
 int IEEE80211_VHT_MCS_NOT_SUPPORTED ; 
 int IEEE80211_VHT_MCS_SUPPORT_0_9 ; 
#define  IWL_AMSDU_12K 132 
#define  IWL_AMSDU_2K 131 
#define  IWL_AMSDU_4K 130 
#define  IWL_AMSDU_8K 129 
#define  IWL_AMSDU_DEF 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 TYPE_4__ iwlwifi_mod_params ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_init_vht_hw_capab(struct iwl_trans *trans,
				  struct iwl_nvm_data *data,
				  struct ieee80211_sta_vht_cap *vht_cap,
				  u8 tx_chains, u8 rx_chains)
{
	const struct iwl_cfg *cfg = trans->cfg;
	int num_rx_ants = num_of_ant(rx_chains);
	int num_tx_ants = num_of_ant(tx_chains);
	unsigned int max_ampdu_exponent = (cfg->max_vht_ampdu_exponent ?:
					   IEEE80211_VHT_MAX_AMPDU_1024K);

	vht_cap->vht_supported = true;

	vht_cap->cap = IEEE80211_VHT_CAP_SHORT_GI_80 |
		       IEEE80211_VHT_CAP_RXSTBC_1 |
		       IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
		       3 << IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT |
		       max_ampdu_exponent <<
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

	if (data->vht160_supported)
		vht_cap->cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ |
				IEEE80211_VHT_CAP_SHORT_GI_160;

	if (cfg->vht_mu_mimo_supported)
		vht_cap->cap |= IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;

	if (cfg->ht_params->ldpc)
		vht_cap->cap |= IEEE80211_VHT_CAP_RXLDPC;

	if (data->sku_cap_mimo_disabled) {
		num_rx_ants = 1;
		num_tx_ants = 1;
	}

	if (num_tx_ants > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	else
		vht_cap->cap |= IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN;

	switch (iwlwifi_mod_params.amsdu_size) {
	case IWL_AMSDU_DEF:
		if (trans->trans_cfg->mq_rx_supported)
			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
		else
			vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895;
		break;
	case IWL_AMSDU_2K:
		if (trans->trans_cfg->mq_rx_supported)
			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
		else
			WARN(1, "RB size of 2K is not supported by this device\n");
		break;
	case IWL_AMSDU_4K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895;
		break;
	case IWL_AMSDU_8K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991;
		break;
	case IWL_AMSDU_12K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
		break;
	default:
		break;
	}

	vht_cap->vht_mcs.rx_mcs_map =
		cpu_to_le16(IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
			    IEEE80211_VHT_MCS_SUPPORT_0_9 << 2 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 14);

	if (num_rx_ants == 1 || cfg->rx_with_siso_diversity) {
		vht_cap->cap |= IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN;
		/* this works because NOT_SUPPORTED == 3 */
		vht_cap->vht_mcs.rx_mcs_map |=
			cpu_to_le16(IEEE80211_VHT_MCS_NOT_SUPPORTED << 2);
	}

	vht_cap->vht_mcs.tx_mcs_map = vht_cap->vht_mcs.rx_mcs_map;

	vht_cap->vht_mcs.tx_highest |=
		cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE);
}