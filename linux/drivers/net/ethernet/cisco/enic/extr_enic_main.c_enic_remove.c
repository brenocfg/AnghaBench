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
struct enic {int /*<<< orphan*/  vdev; int /*<<< orphan*/  pp; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  change_mtu_work; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENIC_SRIOV_ENABLED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enic_dev_deinit (struct enic*) ; 
 int /*<<< orphan*/  enic_iounmap (struct enic*) ; 
 scalar_t__ enic_sriov_enabled (struct enic*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  vnic_dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);

	if (netdev) {
		struct enic *enic = netdev_priv(netdev);

		cancel_work_sync(&enic->reset);
		cancel_work_sync(&enic->change_mtu_work);
		unregister_netdev(netdev);
		enic_dev_deinit(enic);
		vnic_dev_close(enic->vdev);
#ifdef CONFIG_PCI_IOV
		if (enic_sriov_enabled(enic)) {
			pci_disable_sriov(pdev);
			enic->priv_flags &= ~ENIC_SRIOV_ENABLED;
		}
#endif
		kfree(enic->pp);
		vnic_dev_unregister(enic->vdev);
		enic_iounmap(enic);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		free_netdev(netdev);
	}
}