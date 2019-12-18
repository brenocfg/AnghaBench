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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  prev; } ;
struct mt76_dev {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_CB_DMA_DONE ; 
 int /*<<< orphan*/  __mt76_tx_status_skb_done (struct mt76_dev*,struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_tx_status_lock (struct mt76_dev*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_tx_status_unlock (struct mt76_dev*,struct sk_buff_head*) ; 

void mt76_tx_complete_skb(struct mt76_dev *dev, struct sk_buff *skb)
{
	struct sk_buff_head list;

	if (!skb->prev) {
		ieee80211_free_txskb(dev->hw, skb);
		return;
	}

	mt76_tx_status_lock(dev, &list);
	__mt76_tx_status_skb_done(dev, skb, MT_TX_CB_DMA_DONE, &list);
	mt76_tx_status_unlock(dev, &list);
}