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
typedef  scalar_t__ u32 ;
struct rx_ring {scalar_t__ num_rfd; int /*<<< orphan*/  num_ready_recv; int /*<<< orphan*/  recv_list; } ;
struct rfd {int /*<<< orphan*/  list_node; int /*<<< orphan*/ * skb; } ;
struct et131x_adapter {struct rx_ring rx_ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 struct rfd* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et131x_init_recv(struct et131x_adapter *adapter)
{
	struct rfd *rfd;
	u32 rfdct;
	struct rx_ring *rx_ring = &adapter->rx_ring;

	/* Setup each RFD */
	for (rfdct = 0; rfdct < rx_ring->num_rfd; rfdct++) {
		rfd = kzalloc(sizeof(*rfd), GFP_ATOMIC | GFP_DMA);
		if (!rfd)
			return -ENOMEM;

		rfd->skb = NULL;

		/* Add this RFD to the recv_list */
		list_add_tail(&rfd->list_node, &rx_ring->recv_list);

		/* Increment the available RFD's */
		rx_ring->num_ready_recv++;
	}

	return 0;
}