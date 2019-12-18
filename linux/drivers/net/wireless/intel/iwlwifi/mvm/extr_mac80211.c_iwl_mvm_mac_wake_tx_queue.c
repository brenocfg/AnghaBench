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
struct iwl_mvm_txq {scalar_t__ txq_id; int /*<<< orphan*/  list; } ;
struct iwl_mvm {int /*<<< orphan*/  add_stream_wk; int /*<<< orphan*/  add_stream_txqs; } ;
struct ieee80211_txq {scalar_t__ sta; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_MVM_INVALID_QUEUE ; 
 int /*<<< orphan*/  iwl_mvm_mac_itxq_xmit (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 struct iwl_mvm_txq* iwl_mvm_txq_from_mac80211 (struct ieee80211_txq*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void iwl_mvm_mac_wake_tx_queue(struct ieee80211_hw *hw,
				      struct ieee80211_txq *txq)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_txq *mvmtxq = iwl_mvm_txq_from_mac80211(txq);

	/*
	 * Please note that racing is handled very carefully here:
	 * mvmtxq->txq_id is updated during allocation, and mvmtxq->list is
	 * deleted afterwards.
	 * This means that if:
	 * mvmtxq->txq_id != INVALID_QUEUE && list_empty(&mvmtxq->list):
	 *	queue is allocated and we can TX.
	 * mvmtxq->txq_id != INVALID_QUEUE && !list_empty(&mvmtxq->list):
	 *	a race, should defer the frame.
	 * mvmtxq->txq_id == INVALID_QUEUE && list_empty(&mvmtxq->list):
	 *	need to allocate the queue and defer the frame.
	 * mvmtxq->txq_id == INVALID_QUEUE && !list_empty(&mvmtxq->list):
	 *	queue is already scheduled for allocation, no need to allocate,
	 *	should defer the frame.
	 */

	/* If the queue is allocated TX and return. */
	if (!txq->sta || mvmtxq->txq_id != IWL_MVM_INVALID_QUEUE) {
		/*
		 * Check that list is empty to avoid a race where txq_id is
		 * already updated, but the queue allocation work wasn't
		 * finished
		 */
		if (unlikely(txq->sta && !list_empty(&mvmtxq->list)))
			return;

		iwl_mvm_mac_itxq_xmit(hw, txq);
		return;
	}

	/* The list is being deleted only after the queue is fully allocated. */
	if (!list_empty(&mvmtxq->list))
		return;

	list_add_tail(&mvmtxq->list, &mvm->add_stream_txqs);
	schedule_work(&mvm->add_stream_wk);
}