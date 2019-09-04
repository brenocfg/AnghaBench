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
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_BCR_FLR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pci_pcie_cap (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_wait_for_pending_transaction (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nitrox_reset_device(struct pci_dev *pdev)
{
	int pos = 0;

	pos = pci_save_state(pdev);
	if (pos) {
		dev_err(&pdev->dev, "Failed to save pci state\n");
		return -ENOMEM;
	}

	pos = pci_pcie_cap(pdev);
	if (!pos)
		return -ENOTTY;

	if (!pci_wait_for_pending_transaction(pdev))
		dev_err(&pdev->dev, "waiting for pending transaction\n");

	pcie_capability_set_word(pdev, PCI_EXP_DEVCTL, PCI_EXP_DEVCTL_BCR_FLR);
	msleep(100);
	pci_restore_state(pdev);

	return 0;
}