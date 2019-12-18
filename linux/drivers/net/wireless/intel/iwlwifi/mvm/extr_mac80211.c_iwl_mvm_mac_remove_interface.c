#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_probe_resp_data {int dummy; } ;
struct iwl_mvm_vif {size_t id; int /*<<< orphan*/ * phy_ctxt; int /*<<< orphan*/  mcast_sta; int /*<<< orphan*/  probe_resp_data; } ;
struct iwl_mvm {int monitor_on; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * vif_id_to_mac; scalar_t__ vif_count; int /*<<< orphan*/ * p2p_device_vif; scalar_t__ noa_duration; struct ieee80211_vif* noa_vif; int /*<<< orphan*/  ftm_resp_stats; struct iwl_mvm_vif* bf_allowed_vif; } ;
struct TYPE_2__ {scalar_t__ ftm_responder; } ;
struct ieee80211_vif {scalar_t__ type; int driver_flags; TYPE_1__ bss_conf; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int IEEE80211_VIF_BEACON_FILTER ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_remove (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_unref (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_prepare_mac_removal (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_rm_p2p_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_tcm_rm_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_vif_dbgfs_clean (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  kfree_rcu (struct iwl_probe_resp_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iwl_probe_resp_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static void iwl_mvm_mac_remove_interface(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_probe_resp_data *probe_data;

	iwl_mvm_prepare_mac_removal(mvm, vif);

	if (!(vif->type == NL80211_IFTYPE_AP ||
	      vif->type == NL80211_IFTYPE_ADHOC))
		iwl_mvm_tcm_rm_vif(mvm, vif);

	mutex_lock(&mvm->mutex);

	probe_data = rcu_dereference_protected(mvmvif->probe_resp_data,
					       lockdep_is_held(&mvm->mutex));
	RCU_INIT_POINTER(mvmvif->probe_resp_data, NULL);
	if (probe_data)
		kfree_rcu(probe_data, rcu_head);

	if (mvm->bf_allowed_vif == mvmvif) {
		mvm->bf_allowed_vif = NULL;
		vif->driver_flags &= ~(IEEE80211_VIF_BEACON_FILTER |
				       IEEE80211_VIF_SUPPORTS_CQM_RSSI);
	}

	if (vif->bss_conf.ftm_responder)
		memset(&mvm->ftm_resp_stats, 0, sizeof(mvm->ftm_resp_stats));

	iwl_mvm_vif_dbgfs_clean(mvm, vif);

	/*
	 * For AP/GO interface, the tear down of the resources allocated to the
	 * interface is be handled as part of the stop_ap flow.
	 */
	if (vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_ADHOC) {
#ifdef CONFIG_NL80211_TESTMODE
		if (vif == mvm->noa_vif) {
			mvm->noa_vif = NULL;
			mvm->noa_duration = 0;
		}
#endif
		iwl_mvm_dealloc_int_sta(mvm, &mvmvif->mcast_sta);
		iwl_mvm_dealloc_bcast_sta(mvm, vif);
		goto out_release;
	}

	if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {
		mvm->p2p_device_vif = NULL;
		iwl_mvm_rm_p2p_bcast_sta(mvm, vif);
		iwl_mvm_binding_remove_vif(mvm, vif);
		iwl_mvm_phy_ctxt_unref(mvm, mvmvif->phy_ctxt);
		mvmvif->phy_ctxt = NULL;
	}

	if (mvm->vif_count && vif->type != NL80211_IFTYPE_P2P_DEVICE)
		mvm->vif_count--;

	iwl_mvm_power_update_mac(mvm);
	iwl_mvm_mac_ctxt_remove(mvm, vif);

	RCU_INIT_POINTER(mvm->vif_id_to_mac[mvmvif->id], NULL);

	if (vif->type == NL80211_IFTYPE_MONITOR)
		mvm->monitor_on = false;

out_release:
	mutex_unlock(&mvm->mutex);
}