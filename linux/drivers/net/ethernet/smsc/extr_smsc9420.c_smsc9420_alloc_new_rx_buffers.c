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
struct smsc9420_pdata {int rx_ring_tail; int rx_ring_head; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 scalar_t__ smsc9420_alloc_rx_buffer (struct smsc9420_pdata*,int) ; 

__attribute__((used)) static void smsc9420_alloc_new_rx_buffers(struct smsc9420_pdata *pd)
{
	while (pd->rx_ring_tail != pd->rx_ring_head) {
		if (smsc9420_alloc_rx_buffer(pd, pd->rx_ring_tail))
			break;

		pd->rx_ring_tail = (pd->rx_ring_tail + 1) % RX_RING_SIZE;
	}
}