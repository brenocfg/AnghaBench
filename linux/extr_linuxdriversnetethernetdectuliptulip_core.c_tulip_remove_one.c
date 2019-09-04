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
struct tulip_tx_desc {int dummy; } ;
struct tulip_rx_desc {int dummy; } ;
struct tulip_private {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  mtable; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  rx_ring; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct tulip_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void tulip_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata (pdev);
	struct tulip_private *tp;

	if (!dev)
		return;

	tp = netdev_priv(dev);
	unregister_netdev(dev);
	pci_free_consistent (pdev,
			     sizeof (struct tulip_rx_desc) * RX_RING_SIZE +
			     sizeof (struct tulip_tx_desc) * TX_RING_SIZE,
			     tp->rx_ring, tp->rx_ring_dma);
	kfree (tp->mtable);
	pci_iounmap(pdev, tp->base_addr);
	free_netdev (dev);
	pci_release_regions (pdev);
	pci_disable_device(pdev);

	/* pci_power_off (pdev, -1); */
}