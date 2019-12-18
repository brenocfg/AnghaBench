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
struct mt76_txwi_cache {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;
struct mt7615_txp {int nbuf; int /*<<< orphan*/ * len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mt7615_txp* mt7615_txwi_to_txp (struct mt76_dev*,struct mt76_txwi_cache*) ; 

void mt7615_txp_skb_unmap(struct mt76_dev *dev,
			  struct mt76_txwi_cache *t)
{
	struct mt7615_txp *txp;
	int i;

	txp = mt7615_txwi_to_txp(dev, t);
	for (i = 1; i < txp->nbuf; i++)
		dma_unmap_single(dev->dev, le32_to_cpu(txp->buf[i]),
				 le16_to_cpu(txp->len[i]), DMA_TO_DEVICE);
}