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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct mt76_queue_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct mt76_queue {int /*<<< orphan*/  lock; } ;
struct mt76_dev {int /*<<< orphan*/  dev; TYPE_1__* q_tx; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct mt76_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_dma_add_buf (struct mt76_dev*,struct mt76_queue*,struct mt76_queue_buf*,int,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_kick_queue (struct mt76_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76_dma_tx_queue_skb_raw(struct mt76_dev *dev, enum mt76_txq_id qid,
			  struct sk_buff *skb, u32 tx_info)
{
	struct mt76_queue *q = dev->q_tx[qid].q;
	struct mt76_queue_buf buf;
	dma_addr_t addr;

	addr = dma_map_single(dev->dev, skb->data, skb->len,
			      DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(dev->dev, addr)))
		return -ENOMEM;

	buf.addr = addr;
	buf.len = skb->len;

	spin_lock_bh(&q->lock);
	mt76_dma_add_buf(dev, q, &buf, 1, tx_info, skb, NULL);
	mt76_dma_kick_queue(dev, q);
	spin_unlock_bh(&q->lock);

	return 0;
}