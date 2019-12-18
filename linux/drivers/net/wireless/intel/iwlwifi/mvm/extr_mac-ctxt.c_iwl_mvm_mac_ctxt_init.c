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
struct TYPE_6__ {void* sta_id; } ;
struct TYPE_5__ {void* sta_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  list; } ;
struct iwl_mvm_vif {scalar_t__ id; scalar_t__ tsf_id; int /*<<< orphan*/ * smps_requests; void* ap_sta_id; TYPE_3__ mcast_sta; TYPE_2__ bcast_sta; int /*<<< orphan*/  cab_queue; TYPE_1__ time_event_data; scalar_t__ color; } ;
struct iwl_mvm_mac_iface_iterator_data {scalar_t__ preferred_tsf; int found_vif; int /*<<< orphan*/  available_tsf_ids; int /*<<< orphan*/  available_mac_ids; struct ieee80211_vif* vif; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  status; int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  IEEE80211_SMPS_AUTOMATIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_DQA_GCAST_QUEUE ; 
 void* IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
#define  NL80211_IFTYPE_ADHOC 129 
 int NL80211_IFTYPE_AP ; 
 int NL80211_IFTYPE_P2P_DEVICE ; 
#define  NL80211_IFTYPE_STATION 128 
 int NUM_IWL_MVM_SMPS_REQ ; 
 scalar_t__ NUM_MAC_INDEX_DRIVER ; 
 scalar_t__ NUM_TSF_IDS ; 
 int /*<<< orphan*/  TE_MAX ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_mac_iface_iterator_data*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_iface_iterator ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct iwl_mvm_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_mac_ctxt_init(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_mac_iface_iterator_data data = {
		.mvm = mvm,
		.vif = vif,
		.available_mac_ids = { (1 << NUM_MAC_INDEX_DRIVER) - 1 },
		.available_tsf_ids = { (1 << NUM_TSF_IDS) - 1 },
		/* no preference yet */
		.preferred_tsf = NUM_TSF_IDS,
		.found_vif = false,
	};
	int ret, i;

	lockdep_assert_held(&mvm->mutex);

	/*
	 * Allocate a MAC ID and a TSF for this MAC, along with the queues
	 * and other resources.
	 */

	/*
	 * Before the iterator, we start with all MAC IDs and TSFs available.
	 *
	 * During iteration, all MAC IDs are cleared that are in use by other
	 * virtual interfaces, and all TSF IDs are cleared that can't be used
	 * by this new virtual interface because they're used by an interface
	 * that can't share it with the new one.
	 * At the same time, we check if there's a preferred TSF in the case
	 * that we should share it with another interface.
	 */

	/* Currently, MAC ID 0 should be used only for the managed/IBSS vif */
	switch (vif->type) {
	case NL80211_IFTYPE_ADHOC:
		break;
	case NL80211_IFTYPE_STATION:
		if (!vif->p2p)
			break;
		/* fall through */
	default:
		__clear_bit(0, data.available_mac_ids);
	}

	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_mac_iface_iterator, &data);

	/*
	 * In the case we're getting here during resume, it's similar to
	 * firmware restart, and with RESUME_ALL the iterator will find
	 * the vif being added already.
	 * We don't want to reassign any IDs in either case since doing
	 * so would probably assign different IDs (as interfaces aren't
	 * necessarily added in the same order), but the old IDs were
	 * preserved anyway, so skip ID assignment for both resume and
	 * recovery.
	 */
	if (data.found_vif)
		return 0;

	/* Therefore, in recovery, we can't get here */
	if (WARN_ON_ONCE(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)))
		return -EBUSY;

	mvmvif->id = find_first_bit(data.available_mac_ids,
				    NUM_MAC_INDEX_DRIVER);
	if (mvmvif->id == NUM_MAC_INDEX_DRIVER) {
		IWL_ERR(mvm, "Failed to init MAC context - no free ID!\n");
		ret = -EIO;
		goto exit_fail;
	}

	if (data.preferred_tsf != NUM_TSF_IDS)
		mvmvif->tsf_id = data.preferred_tsf;
	else
		mvmvif->tsf_id = find_first_bit(data.available_tsf_ids,
						NUM_TSF_IDS);
	if (mvmvif->tsf_id == NUM_TSF_IDS) {
		IWL_ERR(mvm, "Failed to init MAC context - no free TSF!\n");
		ret = -EIO;
		goto exit_fail;
	}

	mvmvif->color = 0;

	INIT_LIST_HEAD(&mvmvif->time_event_data.list);
	mvmvif->time_event_data.id = TE_MAX;

	/* No need to allocate data queues to P2P Device MAC and NAN.*/
	if (vif->type == NL80211_IFTYPE_P2P_DEVICE)
		return 0;

	/* Allocate the CAB queue for softAP and GO interfaces */
	if (vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_ADHOC) {
		/*
		 * For TVQM this will be overwritten later with the FW assigned
		 * queue value (when queue is enabled).
		 */
		mvmvif->cab_queue = IWL_MVM_DQA_GCAST_QUEUE;
	}

	mvmvif->bcast_sta.sta_id = IWL_MVM_INVALID_STA;
	mvmvif->mcast_sta.sta_id = IWL_MVM_INVALID_STA;
	mvmvif->ap_sta_id = IWL_MVM_INVALID_STA;

	for (i = 0; i < NUM_IWL_MVM_SMPS_REQ; i++)
		mvmvif->smps_requests[i] = IEEE80211_SMPS_AUTOMATIC;

	return 0;

exit_fail:
	memset(mvmvif, 0, sizeof(struct iwl_mvm_vif));
	return ret;
}