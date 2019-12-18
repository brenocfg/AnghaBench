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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_control {int dummy; } ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct TYPE_3__ {size_t q_tx_num; } ;
struct TYPE_4__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {int /*<<< orphan*/ * txqs; TYPE_2__ ah_capabilities; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath5k_tx_queue (struct ieee80211_hw*,struct sk_buff*,int /*<<< orphan*/ *,struct ieee80211_tx_control*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static void
ath5k_tx(struct ieee80211_hw *hw, struct ieee80211_tx_control *control,
	 struct sk_buff *skb)
{
	struct ath5k_hw *ah = hw->priv;
	u16 qnum = skb_get_queue_mapping(skb);

	if (WARN_ON(qnum >= ah->ah_capabilities.cap_queues.q_tx_num)) {
		ieee80211_free_txskb(hw, skb);
		return;
	}

	ath5k_tx_queue(hw, skb, &ah->txqs[qnum], control);
}