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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_txq {int /*<<< orphan*/  ac; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct TYPE_4__ {TYPE_1__ tx_q_state; } ;
struct ath10k {TYPE_2__ htt; } ;

/* Variables and functions */
 scalar_t__ HTT_TX_MODE_SWITCH_PUSH ; 
 int /*<<< orphan*/  ath10k_htt_tx_txq_update (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 scalar_t__ ath10k_mac_tx_can_push (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 int ath10k_mac_tx_push_txq (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 struct ieee80211_txq* ieee80211_next_txq (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_return_txq (struct ieee80211_hw*,struct ieee80211_txq*,int) ; 
 int /*<<< orphan*/  ieee80211_txq_schedule_end (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_txq_schedule_start (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_op_wake_tx_queue(struct ieee80211_hw *hw,
					struct ieee80211_txq *txq)
{
	struct ath10k *ar = hw->priv;
	int ret;
	u8 ac;

	ath10k_htt_tx_txq_update(hw, txq);
	if (ar->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH)
		return;

	ac = txq->ac;
	ieee80211_txq_schedule_start(hw, ac);
	txq = ieee80211_next_txq(hw, ac);
	if (!txq)
		goto out;

	while (ath10k_mac_tx_can_push(hw, txq)) {
		ret = ath10k_mac_tx_push_txq(hw, txq);
		if (ret < 0)
			break;
	}
	ieee80211_return_txq(hw, txq, false);
	ath10k_htt_tx_txq_update(hw, txq);
out:
	ieee80211_txq_schedule_end(hw, ac);
}