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
struct macb_queue {int /*<<< orphan*/ * rx_buffers; int /*<<< orphan*/  rx_buffers_dma; } ;
struct macb {int rx_ring_size; int rx_buffer_size; TYPE_1__* pdev; struct macb_queue* queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macb_free_rx_buffers(struct macb *bp)
{
	struct macb_queue *queue = &bp->queues[0];

	if (queue->rx_buffers) {
		dma_free_coherent(&bp->pdev->dev,
				  bp->rx_ring_size * bp->rx_buffer_size,
				  queue->rx_buffers, queue->rx_buffers_dma);
		queue->rx_buffers = NULL;
	}
}