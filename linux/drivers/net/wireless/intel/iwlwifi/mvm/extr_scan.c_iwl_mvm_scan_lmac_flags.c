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
struct iwl_mvm_scan_params {int n_ssids; int /*<<< orphan*/  type; scalar_t__ pass_all; TYPE_1__* ssids; } ;
struct iwl_mvm {scalar_t__ sched_scan_pass_all; scalar_t__ scan_iter_notif_enabled; TYPE_2__* fw; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_3__ {scalar_t__ ssid_len; } ;

/* Variables and functions */
 int IWL_MVM_LMAC_SCAN_FLAGS_RRM_ENABLED ; 
 int IWL_MVM_LMAC_SCAN_FLAG_EXTENDED_DWELL ; 
 int IWL_MVM_LMAC_SCAN_FLAG_FRAGMENTED ; 
 int IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE ; 
 int IWL_MVM_LMAC_SCAN_FLAG_MATCH ; 
 int IWL_MVM_LMAC_SCAN_FLAG_PASSIVE ; 
 int IWL_MVM_LMAC_SCAN_FLAG_PASS_ALL ; 
 int IWL_MVM_LMAC_SCAN_FLAG_PRE_CONNECTION ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_ENABLED ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_is_regular_scan (struct iwl_mvm_scan_params*) ; 
 scalar_t__ iwl_mvm_is_scan_fragmented (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_rrm_scan_needed (struct iwl_mvm*) ; 

__attribute__((used)) static int iwl_mvm_scan_lmac_flags(struct iwl_mvm *mvm,
				   struct iwl_mvm_scan_params *params,
				   struct ieee80211_vif *vif)
{
	int flags = 0;

	if (params->n_ssids == 0)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_PASSIVE;

	if (params->n_ssids == 1 && params->ssids[0].ssid_len != 0)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_PRE_CONNECTION;

	if (iwl_mvm_is_scan_fragmented(params->type))
		flags |= IWL_MVM_LMAC_SCAN_FLAG_FRAGMENTED;

	if (iwl_mvm_rrm_scan_needed(mvm) &&
	    fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT))
		flags |= IWL_MVM_LMAC_SCAN_FLAGS_RRM_ENABLED;

	if (params->pass_all)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_PASS_ALL;
	else
		flags |= IWL_MVM_LMAC_SCAN_FLAG_MATCH;

#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (mvm->scan_iter_notif_enabled)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE;
#endif

	if (mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_ENABLED)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE;

	if (iwl_mvm_is_regular_scan(params) &&
	    vif->type != NL80211_IFTYPE_P2P_DEVICE &&
	    !iwl_mvm_is_scan_fragmented(params->type))
		flags |= IWL_MVM_LMAC_SCAN_FLAG_EXTENDED_DWELL;

	return flags;
}