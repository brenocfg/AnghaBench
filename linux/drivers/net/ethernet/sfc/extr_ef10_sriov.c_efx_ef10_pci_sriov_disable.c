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
struct efx_nic {scalar_t__ vf_count; int /*<<< orphan*/  net_dev; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_ef10_sriov_free_vf_vswitching (struct efx_nic*) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 unsigned int pci_vfs_assigned (struct pci_dev*) ; 

__attribute__((used)) static int efx_ef10_pci_sriov_disable(struct efx_nic *efx, bool force)
{
	struct pci_dev *dev = efx->pci_dev;
	unsigned int vfs_assigned = 0;

	vfs_assigned = pci_vfs_assigned(dev);

	if (vfs_assigned && !force) {
		netif_info(efx, drv, efx->net_dev, "VFs are assigned to guests; "
			   "please detach them before disabling SR-IOV\n");
		return -EBUSY;
	}

	if (!vfs_assigned)
		pci_disable_sriov(dev);

	efx_ef10_sriov_free_vf_vswitching(efx);
	efx->vf_count = 0;
	return 0;
}