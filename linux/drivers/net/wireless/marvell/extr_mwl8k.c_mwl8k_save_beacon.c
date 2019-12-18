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
struct sk_buff {int dummy; } ;
struct mwl8k_priv {int capture_beacon; int /*<<< orphan*/  finalize_join_worker; int /*<<< orphan*/ * beacon_skb; int /*<<< orphan*/  capture_bssid; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mwl8k_save_beacon(struct ieee80211_hw *hw,
				     struct sk_buff *skb)
{
	struct mwl8k_priv *priv = hw->priv;

	priv->capture_beacon = false;
	eth_zero_addr(priv->capture_bssid);

	/*
	 * Use GFP_ATOMIC as rxq_process is called from
	 * the primary interrupt handler, memory allocation call
	 * must not sleep.
	 */
	priv->beacon_skb = skb_copy(skb, GFP_ATOMIC);
	if (priv->beacon_skb != NULL)
		ieee80211_queue_work(hw, &priv->finalize_join_worker);
}