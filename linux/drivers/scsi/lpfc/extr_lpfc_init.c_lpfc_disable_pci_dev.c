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
struct lpfc_hba {struct pci_dev* pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 

__attribute__((used)) static void
lpfc_disable_pci_dev(struct lpfc_hba *phba)
{
	struct pci_dev *pdev;

	/* Obtain PCI device reference */
	if (!phba->pcidev)
		return;
	else
		pdev = phba->pcidev;
	/* Release PCI resource and disable PCI device */
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);

	return;
}