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

/* Variables and functions */
 scalar_t__ PCI_EXP_DEVSTA ; 
 int /*<<< orphan*/  PCI_EXP_DEVSTA_TRPND ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_cap (struct pci_dev*) ; 
 int pci_wait_for_pending (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

int pci_wait_for_pending_transaction(struct pci_dev *dev)
{
	if (!pci_is_pcie(dev))
		return 1;

	return pci_wait_for_pending(dev, pci_pcie_cap(dev) + PCI_EXP_DEVSTA,
				    PCI_EXP_DEVSTA_TRPND);
}