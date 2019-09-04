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
struct macb_queue {struct macb_dma_desc* tx_ring; int /*<<< orphan*/  bp; } ;
struct macb_dma_desc {int dummy; } ;

/* Variables and functions */
 unsigned int macb_adj_dma_desc_idx (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int macb_tx_ring_wrap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct macb_dma_desc *macb_tx_desc(struct macb_queue *queue,
					  unsigned int index)
{
	index = macb_tx_ring_wrap(queue->bp, index);
	index = macb_adj_dma_desc_idx(queue->bp, index);
	return &queue->tx_ring[index];
}