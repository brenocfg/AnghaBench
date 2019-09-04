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
struct macb_queue {scalar_t__ rx_tail; int /*<<< orphan*/  rx_buffers_dma; struct macb* bp; } ;
struct macb_dma_desc {int /*<<< orphan*/  addr; scalar_t__ ctrl; } ;
struct macb {int rx_ring_size; scalar_t__ rx_buffer_size; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_WRAP ; 
 struct macb_dma_desc* macb_rx_desc (struct macb_queue*,int) ; 
 int /*<<< orphan*/  macb_set_addr (struct macb*,struct macb_dma_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void macb_init_rx_ring(struct macb_queue *queue)
{
	struct macb *bp = queue->bp;
	dma_addr_t addr;
	struct macb_dma_desc *desc = NULL;
	int i;

	addr = queue->rx_buffers_dma;
	for (i = 0; i < bp->rx_ring_size; i++) {
		desc = macb_rx_desc(queue, i);
		macb_set_addr(bp, desc, addr);
		desc->ctrl = 0;
		addr += bp->rx_buffer_size;
	}
	desc->addr |= MACB_BIT(RX_WRAP);
	queue->rx_tail = 0;
}