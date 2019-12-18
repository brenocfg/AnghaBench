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
struct nic {int /*<<< orphan*/  cbs_pool; int /*<<< orphan*/  csr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e100_free (struct nic*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void e100_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);

	if (netdev) {
		struct nic *nic = netdev_priv(netdev);
		unregister_netdev(netdev);
		e100_free(nic);
		pci_iounmap(pdev, nic->csr);
		dma_pool_destroy(nic->cbs_pool);
		free_netdev(netdev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	}
}