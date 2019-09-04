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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fm10k_iov_free_data (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 scalar_t__ pci_num_vf (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 

void fm10k_iov_disable(struct pci_dev *pdev)
{
	if (pci_num_vf(pdev) && pci_vfs_assigned(pdev))
		dev_err(&pdev->dev,
			"Cannot disable SR-IOV while VFs are assigned\n");
	else
		pci_disable_sriov(pdev);

	fm10k_iov_free_data(pdev);
}