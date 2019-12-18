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
struct mt76_txq {int /*<<< orphan*/  retry_q; } ;
struct mt76_dev {int /*<<< orphan*/  hw; } ;
struct ieee80211_txq {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

void mt76_txq_remove(struct mt76_dev *dev, struct ieee80211_txq *txq)
{
	struct mt76_txq *mtxq;
	struct sk_buff *skb;

	if (!txq)
		return;

	mtxq = (struct mt76_txq *)txq->drv_priv;

	while ((skb = skb_dequeue(&mtxq->retry_q)) != NULL)
		ieee80211_free_txskb(dev->hw, skb);
}