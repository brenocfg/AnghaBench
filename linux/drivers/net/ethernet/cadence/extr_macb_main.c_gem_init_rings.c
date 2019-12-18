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
struct macb_queue {scalar_t__ rx_prepared_head; scalar_t__ rx_tail; scalar_t__ tx_tail; scalar_t__ tx_head; } ;
struct macb_dma_desc {int /*<<< orphan*/  ctrl; } ;
struct macb {unsigned int num_queues; int tx_ring_size; struct macb_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_USED ; 
 int /*<<< orphan*/  TX_WRAP ; 
 int /*<<< orphan*/  gem_rx_refill (struct macb_queue*) ; 
 int /*<<< orphan*/  macb_set_addr (struct macb*,struct macb_dma_desc*,int /*<<< orphan*/ ) ; 
 struct macb_dma_desc* macb_tx_desc (struct macb_queue*,int) ; 

__attribute__((used)) static void gem_init_rings(struct macb *bp)
{
	struct macb_queue *queue;
	struct macb_dma_desc *desc = NULL;
	unsigned int q;
	int i;

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		for (i = 0; i < bp->tx_ring_size; i++) {
			desc = macb_tx_desc(queue, i);
			macb_set_addr(bp, desc, 0);
			desc->ctrl = MACB_BIT(TX_USED);
		}
		desc->ctrl |= MACB_BIT(TX_WRAP);
		queue->tx_head = 0;
		queue->tx_tail = 0;

		queue->rx_tail = 0;
		queue->rx_prepared_head = 0;

		gem_rx_refill(queue);
	}

}