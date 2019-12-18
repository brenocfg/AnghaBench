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
struct netdev_private {unsigned int rx_buf_sz; int /*<<< orphan*/ ** rx_skbuff; int /*<<< orphan*/ * rx_dma; int /*<<< orphan*/  pci_dev; TYPE_1__* rx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; scalar_t__ cmd_status; } ;

/* Variables and functions */
 scalar_t__ NATSEMI_PADDING ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drain_rx(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	unsigned int buflen = np->rx_buf_sz;
	int i;

	/* Free all the skbuffs in the Rx queue. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].cmd_status = 0;
		np->rx_ring[i].addr = cpu_to_le32(0xBADF00D0); /* An invalid address. */
		if (np->rx_skbuff[i]) {
			pci_unmap_single(np->pci_dev, np->rx_dma[i],
				buflen + NATSEMI_PADDING,
				PCI_DMA_FROMDEVICE);
			dev_kfree_skb(np->rx_skbuff[i]);
		}
		np->rx_skbuff[i] = NULL;
	}
}