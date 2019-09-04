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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct hamachi_private {int /*<<< orphan*/  base; int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_TOTAL_SIZE ; 
 int /*<<< orphan*/  TX_TOTAL_SIZE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct hamachi_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void hamachi_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);

	if (dev) {
		struct hamachi_private *hmp = netdev_priv(dev);

		pci_free_consistent(pdev, RX_TOTAL_SIZE, hmp->rx_ring,
			hmp->rx_ring_dma);
		pci_free_consistent(pdev, TX_TOTAL_SIZE, hmp->tx_ring,
			hmp->tx_ring_dma);
		unregister_netdev(dev);
		iounmap(hmp->base);
		free_netdev(dev);
		pci_release_regions(pdev);
	}
}