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
struct mwl8k_priv {int /*<<< orphan*/  radio_on; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mwl8k_txq_xmit (struct ieee80211_hw*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mwl8k_tx(struct ieee80211_hw *hw,
		     struct ieee80211_tx_control *control,
		     struct sk_buff *skb)
{
	struct mwl8k_priv *priv = hw->priv;
	int index = skb_get_queue_mapping(skb);

	if (!priv->radio_on) {
		wiphy_debug(hw->wiphy,
			    "dropped TX frame since radio disabled\n");
		dev_kfree_skb(skb);
		return;
	}

	mwl8k_txq_xmit(hw, index, control->sta, skb);
}