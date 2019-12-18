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
struct sk_buff {int dummy; } ;
struct macb_queue {struct sk_buff** rx_skbuff; } ;
struct macb_dma_desc {int dummy; } ;
struct macb {unsigned int num_queues; int rx_ring_size; int /*<<< orphan*/  rx_buffer_size; TYPE_1__* pdev; struct macb_queue* queues; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sk_buff**) ; 
 int /*<<< orphan*/  macb_get_addr (struct macb*,struct macb_dma_desc*) ; 
 struct macb_dma_desc* macb_rx_desc (struct macb_queue*,int) ; 

__attribute__((used)) static void gem_free_rx_buffers(struct macb *bp)
{
	struct sk_buff		*skb;
	struct macb_dma_desc	*desc;
	struct macb_queue *queue;
	dma_addr_t		addr;
	unsigned int q;
	int i;

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		if (!queue->rx_skbuff)
			continue;

		for (i = 0; i < bp->rx_ring_size; i++) {
			skb = queue->rx_skbuff[i];

			if (!skb)
				continue;

			desc = macb_rx_desc(queue, i);
			addr = macb_get_addr(bp, desc);

			dma_unmap_single(&bp->pdev->dev, addr, bp->rx_buffer_size,
					DMA_FROM_DEVICE);
			dev_kfree_skb_any(skb);
			skb = NULL;
		}

		kfree(queue->rx_skbuff);
		queue->rx_skbuff = NULL;
	}
}