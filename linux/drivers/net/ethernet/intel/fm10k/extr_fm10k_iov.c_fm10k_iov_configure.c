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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int fm10k_iov_alloc_data (struct pci_dev*,int) ; 
 int /*<<< orphan*/  fm10k_iov_free_data (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int pci_num_vf (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 

int fm10k_iov_configure(struct pci_dev *pdev, int num_vfs)
{
	int current_vfs = pci_num_vf(pdev);
	int err = 0;

	if (current_vfs && pci_vfs_assigned(pdev)) {
		dev_err(&pdev->dev,
			"Cannot modify SR-IOV while VFs are assigned\n");
		num_vfs = current_vfs;
	} else {
		pci_disable_sriov(pdev);
		fm10k_iov_free_data(pdev);
	}

	/* allocate resources for the VFs */
	err = fm10k_iov_alloc_data(pdev, num_vfs);
	if (err)
		return err;

	/* allocate VFs if not already allocated */
	if (num_vfs && num_vfs != current_vfs) {
		err = pci_enable_sriov(pdev, num_vfs);
		if (err) {
			dev_err(&pdev->dev,
				"Enable PCI SR-IOV failed: %d\n", err);
			return err;
		}
	}

	return num_vfs;
}