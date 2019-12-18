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
struct fe_priv {int /*<<< orphan*/  txrx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rings (struct net_device*) ; 
 int /*<<< orphan*/  get_hwbase (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nv_mgmt_release_sema (struct net_device*) ; 
 int /*<<< orphan*/  nv_restore_mac_addr (struct pci_dev*) ; 
 int /*<<< orphan*/  nv_restore_phy (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void nv_remove(struct pci_dev *pci_dev)
{
	struct net_device *dev = pci_get_drvdata(pci_dev);
	struct fe_priv *np = netdev_priv(dev);

	free_percpu(np->txrx_stats);

	unregister_netdev(dev);

	nv_restore_mac_addr(pci_dev);

	/* restore any phy related changes */
	nv_restore_phy(dev);

	nv_mgmt_release_sema(dev);

	/* free all structures */
	free_rings(dev);
	iounmap(get_hwbase(dev));
	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);
	free_netdev(dev);
}