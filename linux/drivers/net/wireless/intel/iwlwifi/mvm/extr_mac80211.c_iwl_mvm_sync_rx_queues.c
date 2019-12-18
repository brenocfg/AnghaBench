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
struct iwl_mvm_internal_rxq_notif {int sync; int /*<<< orphan*/  type; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_RXQ_EMPTY ; 
 int /*<<< orphan*/  iwl_mvm_sync_rx_queues_internal (struct iwl_mvm*,struct iwl_mvm_internal_rxq_notif*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_sync_rx_queues(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_internal_rxq_notif data = {
		.type = IWL_MVM_RXQ_EMPTY,
		.sync = 1,
	};

	mutex_lock(&mvm->mutex);
	iwl_mvm_sync_rx_queues_internal(mvm, &data, sizeof(data));
	mutex_unlock(&mvm->mutex);
}