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
struct pcnet32_private {int rx_ring_size; scalar_t__* rx_dma_addr; int /*<<< orphan*/ ** rx_skbuff; int /*<<< orphan*/  pci_dev; TYPE_1__* rx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void pcnet32_purge_rx_ring(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	int i;

	/* free all allocated skbuffs */
	for (i = 0; i < lp->rx_ring_size; i++) {
		lp->rx_ring[i].status = 0;	/* CPU owns buffer */
		wmb();		/* Make sure adapter sees owner change */
		if (lp->rx_skbuff[i]) {
			if (!pci_dma_mapping_error(lp->pci_dev,
						   lp->rx_dma_addr[i]))
				pci_unmap_single(lp->pci_dev,
						 lp->rx_dma_addr[i],
						 PKT_BUF_SIZE,
						 PCI_DMA_FROMDEVICE);
			dev_kfree_skb_any(lp->rx_skbuff[i]);
		}
		lp->rx_skbuff[i] = NULL;
		lp->rx_dma_addr[i] = 0;
	}
}