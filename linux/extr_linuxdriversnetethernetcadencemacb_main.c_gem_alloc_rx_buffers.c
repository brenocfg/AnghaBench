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
struct sk_buff {int dummy; } ;
struct macb_queue {int /*<<< orphan*/  rx_skbuff; } ;
struct macb {unsigned int num_queues; int rx_ring_size; int /*<<< orphan*/  dev; struct macb_queue* queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_alloc_rx_buffers(struct macb *bp)
{
	struct macb_queue *queue;
	unsigned int q;
	int size;

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		size = bp->rx_ring_size * sizeof(struct sk_buff *);
		queue->rx_skbuff = kzalloc(size, GFP_KERNEL);
		if (!queue->rx_skbuff)
			return -ENOMEM;
		else
			netdev_dbg(bp->dev,
				   "Allocated %d RX struct sk_buff entries at %p\n",
				   bp->rx_ring_size, queue->rx_skbuff);
	}
	return 0;
}