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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_txq {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ath10k_htt_tx_txq_update (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 scalar_t__ ath10k_mac_tx_can_push (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 int ath10k_mac_tx_push_txq (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 struct ieee80211_txq* ieee80211_next_txq (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_return_txq (struct ieee80211_hw*,struct ieee80211_txq*,int) ; 
 int /*<<< orphan*/  ieee80211_txq_schedule_end (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_txq_schedule_start (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_schedule_txq(struct ieee80211_hw *hw, u32 ac)
{
	struct ieee80211_txq *txq;
	int ret = 0;

	ieee80211_txq_schedule_start(hw, ac);
	while ((txq = ieee80211_next_txq(hw, ac))) {
		while (ath10k_mac_tx_can_push(hw, txq)) {
			ret = ath10k_mac_tx_push_txq(hw, txq);
			if (ret < 0)
				break;
		}
		ieee80211_return_txq(hw, txq, false);
		ath10k_htt_tx_txq_update(hw, txq);
		if (ret == -EBUSY)
			break;
	}
	ieee80211_txq_schedule_end(hw, ac);

	return ret;
}