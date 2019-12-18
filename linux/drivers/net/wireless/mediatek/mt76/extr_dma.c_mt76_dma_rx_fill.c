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
struct mt76_queue_buf {int len; scalar_t__ addr; } ;
struct mt76_queue {int buf_offset; int queued; int ndesc; int /*<<< orphan*/  lock; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  rx_page; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SKB_WITH_OVERHEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int mt76_dma_add_buf (struct mt76_dev*,struct mt76_queue*,struct mt76_queue_buf*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_kick_queue (struct mt76_dev*,struct mt76_queue*) ; 
 void* page_frag_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76_dma_rx_fill(struct mt76_dev *dev, struct mt76_queue *q)
{
	dma_addr_t addr;
	void *buf;
	int frames = 0;
	int len = SKB_WITH_OVERHEAD(q->buf_size);
	int offset = q->buf_offset;
	int idx;

	spin_lock_bh(&q->lock);

	while (q->queued < q->ndesc - 1) {
		struct mt76_queue_buf qbuf;

		buf = page_frag_alloc(&q->rx_page, q->buf_size, GFP_ATOMIC);
		if (!buf)
			break;

		addr = dma_map_single(dev->dev, buf, len, DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(dev->dev, addr))) {
			skb_free_frag(buf);
			break;
		}

		qbuf.addr = addr + offset;
		qbuf.len = len - offset;
		idx = mt76_dma_add_buf(dev, q, &qbuf, 1, 0, buf, NULL);
		frames++;
	}

	if (frames)
		mt76_dma_kick_queue(dev, q);

	spin_unlock_bh(&q->lock);

	return frames;
}