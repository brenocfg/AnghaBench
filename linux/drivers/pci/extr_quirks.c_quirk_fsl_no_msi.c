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
struct pci_dev {int no_msi; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

__attribute__((used)) static void quirk_fsl_no_msi(struct pci_dev *pdev)
{
	if (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT)
		pdev->no_msi = 1;
}