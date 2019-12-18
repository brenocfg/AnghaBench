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
struct sk_buff {int dummy; } ;
struct iwl_mvm_txq {int /*<<< orphan*/  stopped; int /*<<< orphan*/  tx_request; } ;
struct iwl_mvm {TYPE_1__* trans; } ;
struct ieee80211_txq {TYPE_2__* sta; int /*<<< orphan*/  tid; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {scalar_t__ system_pm_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_PLAT_PM_MODE_DISABLED ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_fetch_add_unless (int /*<<< orphan*/ *,int,int) ; 
 struct sk_buff* ieee80211_tx_dequeue (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 int /*<<< orphan*/  iwl_mvm_tx_skb (struct iwl_mvm*,struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_mvm_tx_skb_non_sta (struct iwl_mvm*,struct sk_buff*) ; 
 struct iwl_mvm_txq* iwl_mvm_txq_from_mac80211 (struct ieee80211_txq*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void iwl_mvm_mac_itxq_xmit(struct ieee80211_hw *hw, struct ieee80211_txq *txq)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_txq *mvmtxq = iwl_mvm_txq_from_mac80211(txq);
	struct sk_buff *skb = NULL;

	/*
	 * No need for threads to be pending here, they can leave the first
	 * taker all the work.
	 *
	 * mvmtxq->tx_request logic:
	 *
	 * If 0, no one is currently TXing, set to 1 to indicate current thread
	 * will now start TX and other threads should quit.
	 *
	 * If 1, another thread is currently TXing, set to 2 to indicate to
	 * that thread that there was another request. Since that request may
	 * have raced with the check whether the queue is empty, the TXing
	 * thread should check the queue's status one more time before leaving.
	 * This check is done in order to not leave any TX hanging in the queue
	 * until the next TX invocation (which may not even happen).
	 *
	 * If 2, another thread is currently TXing, and it will already double
	 * check the queue, so do nothing.
	 */
	if (atomic_fetch_add_unless(&mvmtxq->tx_request, 1, 2))
		return;

	rcu_read_lock();
	do {
		while (likely(!mvmtxq->stopped &&
			      (mvm->trans->system_pm_mode ==
			       IWL_PLAT_PM_MODE_DISABLED))) {
			skb = ieee80211_tx_dequeue(hw, txq);

			if (!skb) {
				if (txq->sta)
					IWL_DEBUG_TX(mvm,
						     "TXQ of sta %pM tid %d is now empty\n",
						     txq->sta->addr,
						     txq->tid);
				break;
			}

			if (!txq->sta)
				iwl_mvm_tx_skb_non_sta(mvm, skb);
			else
				iwl_mvm_tx_skb(mvm, skb, txq->sta);
		}
	} while (atomic_dec_return(&mvmtxq->tx_request));
	rcu_read_unlock();
}