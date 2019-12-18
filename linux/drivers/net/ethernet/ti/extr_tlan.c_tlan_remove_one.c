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
struct tlan_priv {int /*<<< orphan*/  tlan_tqueue; int /*<<< orphan*/  dma_storage_dma; scalar_t__ dma_storage; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  pci_dev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void tlan_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct tlan_priv	*priv = netdev_priv(dev);

	unregister_netdev(dev);

	if (priv->dma_storage) {
		pci_free_consistent(priv->pci_dev,
				    priv->dma_size, priv->dma_storage,
				    priv->dma_storage_dma);
	}

#ifdef CONFIG_PCI
	pci_release_regions(pdev);
#endif

	free_netdev(dev);

	cancel_work_sync(&priv->tlan_tqueue);
}