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
struct iwl_mvm_sta {int reserved_queue; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {TYPE_1__* queue_info; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  tid_bitmap; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 size_t IWL_MVM_DQA_BSS_CLIENT_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MAX_DATA_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MIN_DATA_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_FREE ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_RESERVED ; 
 int NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int iwl_mvm_find_free_queue (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_inactivity_check (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 

__attribute__((used)) static int iwl_mvm_reserve_sta_stream(struct iwl_mvm *mvm,
				      struct ieee80211_sta *sta,
				      enum nl80211_iftype vif_type)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	int queue;

	/* queue reserving is disabled on new TX path */
	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return 0;

	/* run the general cleanup/unsharing of queues */
	iwl_mvm_inactivity_check(mvm, IWL_MVM_INVALID_STA);

	/* Make sure we have free resources for this STA */
	if (vif_type == NL80211_IFTYPE_STATION && !sta->tdls &&
	    !mvm->queue_info[IWL_MVM_DQA_BSS_CLIENT_QUEUE].tid_bitmap &&
	    (mvm->queue_info[IWL_MVM_DQA_BSS_CLIENT_QUEUE].status ==
	     IWL_MVM_QUEUE_FREE))
		queue = IWL_MVM_DQA_BSS_CLIENT_QUEUE;
	else
		queue = iwl_mvm_find_free_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_DATA_QUEUE,
						IWL_MVM_DQA_MAX_DATA_QUEUE);
	if (queue < 0) {
		/* try again - this time kick out a queue if needed */
		queue = iwl_mvm_inactivity_check(mvm, mvmsta->sta_id);
		if (queue < 0) {
			IWL_ERR(mvm, "No available queues for new station\n");
			return -ENOSPC;
		}
	}
	mvm->queue_info[queue].status = IWL_MVM_QUEUE_RESERVED;

	mvmsta->reserved_queue = queue;

	IWL_DEBUG_TX_QUEUES(mvm, "Reserving data queue #%d for sta_id %d\n",
			    queue, mvmsta->sta_id);

	return 0;
}