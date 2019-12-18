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
typedef  int u16 ;
struct pnv_php_slot {int irq; int /*<<< orphan*/ * wq; struct pci_dev* pdev; } ;
struct pci_dev {scalar_t__ msi_enabled; scalar_t__ msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int PCI_EXP_SLTCTL_DLLSCE ; 
 int PCI_EXP_SLTCTL_HPIE ; 
 int PCI_EXP_SLTCTL_PDCE ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct pnv_php_slot*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pnv_php_disable_irq(struct pnv_php_slot *php_slot,
				bool disable_device)
{
	struct pci_dev *pdev = php_slot->pdev;
	int irq = php_slot->irq;
	u16 ctrl;

	if (php_slot->irq > 0) {
		pcie_capability_read_word(pdev, PCI_EXP_SLTCTL, &ctrl);
		ctrl &= ~(PCI_EXP_SLTCTL_HPIE |
			  PCI_EXP_SLTCTL_PDCE |
			  PCI_EXP_SLTCTL_DLLSCE);
		pcie_capability_write_word(pdev, PCI_EXP_SLTCTL, ctrl);

		free_irq(php_slot->irq, php_slot);
		php_slot->irq = 0;
	}

	if (php_slot->wq) {
		destroy_workqueue(php_slot->wq);
		php_slot->wq = NULL;
	}

	if (disable_device || irq > 0) {
		if (pdev->msix_enabled)
			pci_disable_msix(pdev);
		else if (pdev->msi_enabled)
			pci_disable_msi(pdev);

		pci_disable_device(pdev);
	}
}