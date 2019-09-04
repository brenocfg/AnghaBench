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
struct macb_queue {int tx_ring_dma; int /*<<< orphan*/  bp; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int macb_dma_desc_get_size (int /*<<< orphan*/ ) ; 
 int macb_tx_ring_wrap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static dma_addr_t macb_tx_dma(struct macb_queue *queue, unsigned int index)
{
	dma_addr_t offset;

	offset = macb_tx_ring_wrap(queue->bp, index) *
			macb_dma_desc_get_size(queue->bp);

	return queue->tx_ring_dma + offset;
}