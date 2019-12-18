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
struct netdev_private {int /*<<< orphan*/  eeprom_addr; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  rx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_TOTAL_SIZE ; 
 int /*<<< orphan*/  TX_TOTAL_SIZE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
rio_remove1 (struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata (pdev);

	if (dev) {
		struct netdev_private *np = netdev_priv(dev);

		unregister_netdev (dev);
		pci_free_consistent (pdev, RX_TOTAL_SIZE, np->rx_ring,
				     np->rx_ring_dma);
		pci_free_consistent (pdev, TX_TOTAL_SIZE, np->tx_ring,
				     np->tx_ring_dma);
#ifdef MEM_MAPPING
		pci_iounmap(pdev, np->ioaddr);
#endif
		pci_iounmap(pdev, np->eeprom_addr);
		free_netdev (dev);
		pci_release_regions (pdev);
		pci_disable_device (pdev);
	}
}