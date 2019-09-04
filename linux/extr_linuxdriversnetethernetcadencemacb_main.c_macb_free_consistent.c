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
struct macb_queue {int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/ * tx_skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mog_free_rx_buffers ) (struct macb*) ;} ;
struct macb {unsigned int num_queues; int tx_bd_rd_prefetch; int rx_bd_rd_prefetch; TYPE_2__* pdev; struct macb_queue* queues; TYPE_1__ macbgem_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RX_RING_BYTES (struct macb*) ; 
 int TX_RING_BYTES (struct macb*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct macb*) ; 

__attribute__((used)) static void macb_free_consistent(struct macb *bp)
{
	struct macb_queue *queue;
	unsigned int q;
	int size;

	bp->macbgem_ops.mog_free_rx_buffers(bp);

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		kfree(queue->tx_skb);
		queue->tx_skb = NULL;
		if (queue->tx_ring) {
			size = TX_RING_BYTES(bp) + bp->tx_bd_rd_prefetch;
			dma_free_coherent(&bp->pdev->dev, size,
					  queue->tx_ring, queue->tx_ring_dma);
			queue->tx_ring = NULL;
		}
		if (queue->rx_ring) {
			size = RX_RING_BYTES(bp) + bp->rx_bd_rd_prefetch;
			dma_free_coherent(&bp->pdev->dev, size,
					  queue->rx_ring, queue->rx_ring_dma);
			queue->rx_ring = NULL;
		}
	}
}