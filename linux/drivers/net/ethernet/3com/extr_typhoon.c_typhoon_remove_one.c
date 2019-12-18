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
struct typhoon_shared {int dummy; } ;
struct typhoon {int /*<<< orphan*/  shared_dma; int /*<<< orphan*/  shared; int /*<<< orphan*/  ioaddr; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NoWait ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_clear_mwi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
typhoon_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct typhoon *tp = netdev_priv(dev);

	unregister_netdev(dev);
	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	typhoon_reset(tp->ioaddr, NoWait);
	pci_iounmap(pdev, tp->ioaddr);
	pci_free_consistent(pdev, sizeof(struct typhoon_shared),
			    tp->shared, tp->shared_dma);
	pci_release_regions(pdev);
	pci_clear_mwi(pdev);
	pci_disable_device(pdev);
	free_netdev(dev);
}