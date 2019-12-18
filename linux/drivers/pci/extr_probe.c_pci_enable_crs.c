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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_RTCAP ; 
 int PCI_EXP_RTCAP_CRSVIS ; 
 int /*<<< orphan*/  PCI_EXP_RTCTL ; 
 int /*<<< orphan*/  PCI_EXP_RTCTL_CRSSVE ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_enable_crs(struct pci_dev *pdev)
{
	u16 root_cap = 0;

	/* Enable CRS Software Visibility if supported */
	pcie_capability_read_word(pdev, PCI_EXP_RTCAP, &root_cap);
	if (root_cap & PCI_EXP_RTCAP_CRSVIS)
		pcie_capability_set_word(pdev, PCI_EXP_RTCTL,
					 PCI_EXP_RTCTL_CRSSVE);
}