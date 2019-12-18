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
struct pcnet32_tx_head {int dummy; } ;
struct pcnet32_rx_head {int dummy; } ;
struct pcnet32_private {int tx_ring_size; int rx_ring_size; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma_addr; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_ring_dma_addr; int /*<<< orphan*/ * rx_dma_addr; int /*<<< orphan*/ * tx_dma_addr; int /*<<< orphan*/ * rx_skbuff; int /*<<< orphan*/ * tx_skbuff; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcnet32_free_ring(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);

	kfree(lp->tx_skbuff);
	lp->tx_skbuff = NULL;

	kfree(lp->rx_skbuff);
	lp->rx_skbuff = NULL;

	kfree(lp->tx_dma_addr);
	lp->tx_dma_addr = NULL;

	kfree(lp->rx_dma_addr);
	lp->rx_dma_addr = NULL;

	if (lp->tx_ring) {
		pci_free_consistent(lp->pci_dev,
				    sizeof(struct pcnet32_tx_head) *
				    lp->tx_ring_size, lp->tx_ring,
				    lp->tx_ring_dma_addr);
		lp->tx_ring = NULL;
	}

	if (lp->rx_ring) {
		pci_free_consistent(lp->pci_dev,
				    sizeof(struct pcnet32_rx_head) *
				    lp->rx_ring_size, lp->rx_ring,
				    lp->rx_ring_dma_addr);
		lp->rx_ring = NULL;
	}
}