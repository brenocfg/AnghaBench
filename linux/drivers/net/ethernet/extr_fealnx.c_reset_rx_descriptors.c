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
struct netdev_private {scalar_t__ mem; scalar_t__ rx_ring; struct fealnx_desc* cur_rx; scalar_t__ rx_ring_dma; } ;
struct net_device {int dummy; } ;
struct fealnx_desc {struct fealnx_desc* next_desc_logical; int /*<<< orphan*/  status; scalar_t__ skbuff; } ;

/* Variables and functions */
 scalar_t__ RXLBA ; 
 int /*<<< orphan*/  RXOWN ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  allocate_rx_buffers (struct net_device*) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void reset_rx_descriptors(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	struct fealnx_desc *cur = np->cur_rx;
	int i;

	allocate_rx_buffers(dev);

	for (i = 0; i < RX_RING_SIZE; i++) {
		if (cur->skbuff)
			cur->status = RXOWN;
		cur = cur->next_desc_logical;
	}

	iowrite32(np->rx_ring_dma + ((char*)np->cur_rx - (char*)np->rx_ring),
		np->mem + RXLBA);
}