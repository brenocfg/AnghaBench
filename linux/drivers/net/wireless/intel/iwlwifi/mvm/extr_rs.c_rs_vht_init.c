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
struct iwl_mvm {TYPE_3__* fw; TYPE_2__* cfg; } ;
struct iwl_lq_sta {int ldpc; int stbc_capable; int bfer_capable; int is_vht; } ;
struct ieee80211_sta_vht_cap {int cap; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_5__ {TYPE_1__* ht_params; } ;
struct TYPE_4__ {scalar_t__ stbc; scalar_t__ ldpc; } ;

/* Variables and functions */
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_MASK ; 
 int IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_BEAMFORMER ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_vht_set_enabled_rates (struct ieee80211_sta*,struct ieee80211_sta_vht_cap*,struct iwl_lq_sta*) ; 

__attribute__((used)) static void rs_vht_init(struct iwl_mvm *mvm,
			struct ieee80211_sta *sta,
			struct iwl_lq_sta *lq_sta,
			struct ieee80211_sta_vht_cap *vht_cap)
{
	rs_vht_set_enabled_rates(sta, vht_cap, lq_sta);

	if (mvm->cfg->ht_params->ldpc &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC))
		lq_sta->ldpc = true;

	if (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK))
		lq_sta->stbc_capable = true;

	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_BEAMFORMER) &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE))
		lq_sta->bfer_capable = true;

	lq_sta->is_vht = true;
}