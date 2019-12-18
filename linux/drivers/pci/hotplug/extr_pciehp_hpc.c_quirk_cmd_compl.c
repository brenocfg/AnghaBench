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
typedef  int u32 ;
struct pci_dev {int broken_cmd_compl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTCAP ; 
 int PCI_EXP_SLTCAP_HPC ; 
 int PCI_EXP_SLTCAP_NCCS ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void quirk_cmd_compl(struct pci_dev *pdev)
{
	u32 slot_cap;

	if (pci_is_pcie(pdev)) {
		pcie_capability_read_dword(pdev, PCI_EXP_SLTCAP, &slot_cap);
		if (slot_cap & PCI_EXP_SLTCAP_HPC &&
		    !(slot_cap & PCI_EXP_SLTCAP_NCCS))
			pdev->broken_cmd_compl = 1;
	}
}