#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_1__* bus; } ;
struct hfi1_devdata {struct pci_dev* pcidev; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL_ASPMC ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL_ASPM_L1 ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspm_hw_enable_l1(struct hfi1_devdata *dd)
{
	struct pci_dev *parent = dd->pcidev->bus->self;

	/*
	 * If the driver does not have access to the upstream component,
	 * it cannot support ASPM L1 at all.
	 */
	if (!parent)
		return;

	/* Enable ASPM L1 first in upstream component and then downstream */
	pcie_capability_clear_and_set_word(parent, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC,
					   PCI_EXP_LNKCTL_ASPM_L1);
	pcie_capability_clear_and_set_word(dd->pcidev, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC,
					   PCI_EXP_LNKCTL_ASPM_L1);
}