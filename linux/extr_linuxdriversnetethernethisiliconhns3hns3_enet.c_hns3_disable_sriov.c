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
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 

__attribute__((used)) static void hns3_disable_sriov(struct pci_dev *pdev)
{
	/* If our VFs are assigned we cannot shut down SR-IOV
	 * without causing issues, so just leave the hardware
	 * available but disabled
	 */
	if (pci_vfs_assigned(pdev)) {
		dev_warn(&pdev->dev,
			 "disabling driver while VFs are assigned\n");
		return;
	}

	pci_disable_sriov(pdev);
}