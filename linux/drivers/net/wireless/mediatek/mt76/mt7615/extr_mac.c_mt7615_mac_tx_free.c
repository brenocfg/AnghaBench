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
typedef  size_t u8 ;
struct sk_buff {scalar_t__ data; } ;
struct mt76_txwi_cache {int /*<<< orphan*/ * skb; } ;
struct mt76_dev {int dummy; } ;
struct mt7615_tx_free {int /*<<< orphan*/ * token; int /*<<< orphan*/  ctrl; } ;
struct mt7615_dev {int /*<<< orphan*/  token_lock; int /*<<< orphan*/  token; struct mt76_dev mt76; } ;

/* Variables and functions */
 size_t FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_TX_FREE_MSDU_ID_CNT ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct mt76_txwi_cache* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7615_txp_skb_unmap (struct mt76_dev*,struct mt76_txwi_cache*) ; 
 int /*<<< orphan*/  mt76_put_txwi (struct mt76_dev*,struct mt76_txwi_cache*) ; 
 int /*<<< orphan*/  mt76_tx_complete_skb (struct mt76_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt7615_mac_tx_free(struct mt7615_dev *dev, struct sk_buff *skb)
{
	struct mt7615_tx_free *free = (struct mt7615_tx_free *)skb->data;
	struct mt76_dev *mdev = &dev->mt76;
	struct mt76_txwi_cache *txwi;
	u8 i, count;

	count = FIELD_GET(MT_TX_FREE_MSDU_ID_CNT, le16_to_cpu(free->ctrl));
	for (i = 0; i < count; i++) {
		spin_lock_bh(&dev->token_lock);
		txwi = idr_remove(&dev->token, le16_to_cpu(free->token[i]));
		spin_unlock_bh(&dev->token_lock);

		if (!txwi)
			continue;

		mt7615_txp_skb_unmap(mdev, txwi);
		if (txwi->skb) {
			mt76_tx_complete_skb(mdev, txwi->skb);
			txwi->skb = NULL;
		}

		mt76_put_txwi(mdev, txwi);
	}
	dev_kfree_skb(skb);
}