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
struct pci_dev {scalar_t__ is_virtfn; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_ENDPOINT ; 
 scalar_t__ PCI_EXP_TYPE_LEG_END ; 
 scalar_t__ PCI_EXP_TYPE_UPSTREAM ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pcie_print_link_status (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

void pcie_report_downtraining(struct pci_dev *dev)
{
	if (!pci_is_pcie(dev))
		return;

	/* Look from the device up to avoid downstream ports with no devices */
	if ((pci_pcie_type(dev) != PCI_EXP_TYPE_ENDPOINT) &&
	    (pci_pcie_type(dev) != PCI_EXP_TYPE_LEG_END) &&
	    (pci_pcie_type(dev) != PCI_EXP_TYPE_UPSTREAM))
		return;

	/* Multi-function PCIe devices share the same link/status */
	if (PCI_FUNC(dev->devfn) != 0 || dev->is_virtfn)
		return;

	/* Print link status only if the device is constrained by the fabric */
	__pcie_print_link_status(dev, false);
}