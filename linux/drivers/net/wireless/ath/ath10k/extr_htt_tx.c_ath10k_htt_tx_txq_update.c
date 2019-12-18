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
struct ieee80211_txq {int dummy; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath10k {TYPE_1__ htt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ath10k_htt_tx_txq_recalc (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 int /*<<< orphan*/  __ath10k_htt_tx_txq_sync (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath10k_htt_tx_txq_update(struct ieee80211_hw *hw,
			      struct ieee80211_txq *txq)
{
	struct ath10k *ar = hw->priv;

	spin_lock_bh(&ar->htt.tx_lock);
	__ath10k_htt_tx_txq_recalc(hw, txq);
	__ath10k_htt_tx_txq_sync(ar);
	spin_unlock_bh(&ar->htt.tx_lock);
}