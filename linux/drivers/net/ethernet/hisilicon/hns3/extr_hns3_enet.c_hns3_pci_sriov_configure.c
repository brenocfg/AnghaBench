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
 int /*<<< orphan*/  CONFIG_PCI_IOV ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hns3_is_phys_func (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_vfs_assigned (struct pci_dev*) ; 

__attribute__((used)) static int hns3_pci_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	int ret;

	if (!(hns3_is_phys_func(pdev) && IS_ENABLED(CONFIG_PCI_IOV))) {
		dev_warn(&pdev->dev, "Can not config SRIOV\n");
		return -EINVAL;
	}

	if (num_vfs) {
		ret = pci_enable_sriov(pdev, num_vfs);
		if (ret)
			dev_err(&pdev->dev, "SRIOV enable failed %d\n", ret);
		else
			return num_vfs;
	} else if (!pci_vfs_assigned(pdev)) {
		pci_disable_sriov(pdev);
	} else {
		dev_warn(&pdev->dev,
			 "Unable to free VFs because some are assigned to VMs.\n");
	}

	return 0;
}