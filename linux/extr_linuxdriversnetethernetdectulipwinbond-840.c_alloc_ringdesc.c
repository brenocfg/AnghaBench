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
struct w840_tx_desc {int dummy; } ;
struct w840_rx_desc {int dummy; } ;
struct netdev_private {int rx_buf_sz; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  ring_dma_addr; int /*<<< orphan*/  pci_dev; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  init_rxtx_rings (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_ringdesc(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);

	np->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	np->rx_ring = pci_alloc_consistent(np->pci_dev,
			sizeof(struct w840_rx_desc)*RX_RING_SIZE +
			sizeof(struct w840_tx_desc)*TX_RING_SIZE,
			&np->ring_dma_addr);
	if(!np->rx_ring)
		return -ENOMEM;
	init_rxtx_rings(dev);
	return 0;
}