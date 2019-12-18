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
typedef  int u16 ;
struct iwl_mvm {TYPE_3__* cfg; } ;
struct iwl_lq_sta {int active_siso_rate; int active_mimo2_rate; int ldpc; int stbc_capable; int is_vht; } ;
struct TYPE_4__ {int* rx_mask; } ;
struct ieee80211_sta_ht_cap {int cap; TYPE_1__ mcs; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ht_params; } ;
struct TYPE_5__ {scalar_t__ stbc; scalar_t__ ldpc; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IWL_FIRST_OFDM_RATE ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_ht_init(struct iwl_mvm *mvm,
		       struct ieee80211_sta *sta,
		       struct iwl_lq_sta *lq_sta,
		       struct ieee80211_sta_ht_cap *ht_cap)
{
	/* active_siso_rate mask includes 9 MBits (bit 5),
	 * and CCK (bits 0-3), supp_rates[] does not;
	 * shift to convert format, force 9 MBits off.
	 */
	lq_sta->active_siso_rate = ht_cap->mcs.rx_mask[0] << 1;
	lq_sta->active_siso_rate |= ht_cap->mcs.rx_mask[0] & 0x1;
	lq_sta->active_siso_rate &= ~((u16)0x2);
	lq_sta->active_siso_rate <<= IWL_FIRST_OFDM_RATE;

	lq_sta->active_mimo2_rate = ht_cap->mcs.rx_mask[1] << 1;
	lq_sta->active_mimo2_rate |= ht_cap->mcs.rx_mask[1] & 0x1;
	lq_sta->active_mimo2_rate &= ~((u16)0x2);
	lq_sta->active_mimo2_rate <<= IWL_FIRST_OFDM_RATE;

	if (mvm->cfg->ht_params->ldpc &&
	    (ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING))
		lq_sta->ldpc = true;

	if (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC))
		lq_sta->stbc_capable = true;

	lq_sta->is_vht = false;
}