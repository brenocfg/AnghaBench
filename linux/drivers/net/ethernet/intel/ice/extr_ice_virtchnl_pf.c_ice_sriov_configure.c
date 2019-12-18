#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ice_free_vfs (struct ice_pf*) ; 
 scalar_t__ ice_is_safe_mode (struct ice_pf*) ; 
 int ice_pci_sriov_ena (struct ice_pf*,int) ; 
 struct ice_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (struct pci_dev*) ; 

int ice_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct ice_pf *pf = pci_get_drvdata(pdev);

	if (ice_is_safe_mode(pf)) {
		dev_err(&pf->pdev->dev,
			"SR-IOV cannot be configured - Device is in Safe Mode\n");
		return -EOPNOTSUPP;
	}

	if (num_vfs)
		return ice_pci_sriov_ena(pf, num_vfs);

	if (!pci_vfs_assigned(pdev)) {
		ice_free_vfs(pf);
	} else {
		dev_err(&pf->pdev->dev,
			"can't free VFs because some are assigned to VMs.\n");
		return -EBUSY;
	}

	return 0;
}