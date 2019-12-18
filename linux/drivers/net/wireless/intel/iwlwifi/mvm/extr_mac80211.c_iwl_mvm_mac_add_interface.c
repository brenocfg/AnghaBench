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
struct TYPE_2__ {scalar_t__ num_beacons; int /*<<< orphan*/  accu_num_beacons; } ;
struct iwl_mvm_vif {size_t id; int /*<<< orphan*/ * phy_ctxt; int /*<<< orphan*/  csa_work; int /*<<< orphan*/  features; int /*<<< orphan*/  mcast_sta; TYPE_1__ beacon_stats; int /*<<< orphan*/  probe_resp_data; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int monitor_on; int /*<<< orphan*/  mutex; int /*<<< orphan*/  vif_count; struct iwl_mvm_vif* bf_allowed_vif; struct ieee80211_vif* p2p_device_vif; int /*<<< orphan*/ * vif_id_to_mac; int /*<<< orphan*/  status; } ;
struct ieee80211_vif {int driver_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  p2p; } ;
struct ieee80211_hw {int /*<<< orphan*/  netdev_features; } ;

/* Variables and functions */
 int ENOSPC ; 
 int IEEE80211_VIF_BEACON_FILTER ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  IWL_STA_MULTICAST ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iwl_mvm_add_p2p_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_alloc_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_allocate_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_binding_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_channel_switch_disconnect_wk ; 
 int iwl_mvm_disable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iwl_mvm_get_free_phy_ctxt (struct iwl_mvm*) ; 
 int iwl_mvm_mac_ctxt_add (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_init (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_remove (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_ref (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_unref (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_tcm_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_vif_dbgfs_register (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_mac_add_interface(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	mvmvif->mvm = mvm;
	RCU_INIT_POINTER(mvmvif->probe_resp_data, NULL);

	/*
	 * Not much to do here. The stack will not allow interface
	 * types or combinations that we didn't advertise, so we
	 * don't really have to check the types.
	 */

	mutex_lock(&mvm->mutex);

	/* make sure that beacon statistics don't go backwards with FW reset */
	if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		mvmvif->beacon_stats.accu_num_beacons +=
			mvmvif->beacon_stats.num_beacons;

	/* Allocate resources for the MAC context, and add it to the fw  */
	ret = iwl_mvm_mac_ctxt_init(mvm, vif);
	if (ret)
		goto out_unlock;

	rcu_assign_pointer(mvm->vif_id_to_mac[mvmvif->id], vif);

	/* Counting number of interfaces is needed for legacy PM */
	if (vif->type != NL80211_IFTYPE_P2P_DEVICE)
		mvm->vif_count++;

	/*
	 * The AP binding flow can be done only after the beacon
	 * template is configured (which happens only in the mac80211
	 * start_ap() flow), and adding the broadcast station can happen
	 * only after the binding.
	 * In addition, since modifying the MAC before adding a bcast
	 * station is not allowed by the FW, delay the adding of MAC context to
	 * the point where we can also add the bcast station.
	 * In short: there's not much we can do at this point, other than
	 * allocating resources :)
	 */
	if (vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_ADHOC) {
		ret = iwl_mvm_alloc_bcast_sta(mvm, vif);
		if (ret) {
			IWL_ERR(mvm, "Failed to allocate bcast sta\n");
			goto out_release;
		}

		/*
		 * Only queue for this station is the mcast queue,
		 * which shouldn't be in TFD mask anyway
		 */
		ret = iwl_mvm_allocate_int_sta(mvm, &mvmvif->mcast_sta,
					       0, vif->type,
					       IWL_STA_MULTICAST);
		if (ret)
			goto out_release;

		iwl_mvm_vif_dbgfs_register(mvm, vif);
		goto out_unlock;
	}

	mvmvif->features |= hw->netdev_features;

	ret = iwl_mvm_mac_ctxt_add(mvm, vif);
	if (ret)
		goto out_release;

	ret = iwl_mvm_power_update_mac(mvm);
	if (ret)
		goto out_remove_mac;

	/* beacon filtering */
	ret = iwl_mvm_disable_beacon_filter(mvm, vif, 0);
	if (ret)
		goto out_remove_mac;

	if (!mvm->bf_allowed_vif &&
	    vif->type == NL80211_IFTYPE_STATION && !vif->p2p) {
		mvm->bf_allowed_vif = mvmvif;
		vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
				     IEEE80211_VIF_SUPPORTS_CQM_RSSI;
	}

	/*
	 * P2P_DEVICE interface does not have a channel context assigned to it,
	 * so a dedicated PHY context is allocated to it and the corresponding
	 * MAC context is bound to it at this stage.
	 */
	if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {

		mvmvif->phy_ctxt = iwl_mvm_get_free_phy_ctxt(mvm);
		if (!mvmvif->phy_ctxt) {
			ret = -ENOSPC;
			goto out_free_bf;
		}

		iwl_mvm_phy_ctxt_ref(mvm, mvmvif->phy_ctxt);
		ret = iwl_mvm_binding_add_vif(mvm, vif);
		if (ret)
			goto out_unref_phy;

		ret = iwl_mvm_add_p2p_bcast_sta(mvm, vif);
		if (ret)
			goto out_unbind;

		/* Save a pointer to p2p device vif, so it can later be used to
		 * update the p2p device MAC when a GO is started/stopped */
		mvm->p2p_device_vif = vif;
	}

	iwl_mvm_tcm_add_vif(mvm, vif);
	INIT_DELAYED_WORK(&mvmvif->csa_work,
			  iwl_mvm_channel_switch_disconnect_wk);

	if (vif->type == NL80211_IFTYPE_MONITOR)
		mvm->monitor_on = true;

	iwl_mvm_vif_dbgfs_register(mvm, vif);
	goto out_unlock;

 out_unbind:
	iwl_mvm_binding_remove_vif(mvm, vif);
 out_unref_phy:
	iwl_mvm_phy_ctxt_unref(mvm, mvmvif->phy_ctxt);
 out_free_bf:
	if (mvm->bf_allowed_vif == mvmvif) {
		mvm->bf_allowed_vif = NULL;
		vif->driver_flags &= ~(IEEE80211_VIF_BEACON_FILTER |
				       IEEE80211_VIF_SUPPORTS_CQM_RSSI);
	}
 out_remove_mac:
	mvmvif->phy_ctxt = NULL;
	iwl_mvm_mac_ctxt_remove(mvm, vif);
 out_release:
	if (vif->type != NL80211_IFTYPE_P2P_DEVICE)
		mvm->vif_count--;
 out_unlock:
	mutex_unlock(&mvm->mutex);

	return ret;
}