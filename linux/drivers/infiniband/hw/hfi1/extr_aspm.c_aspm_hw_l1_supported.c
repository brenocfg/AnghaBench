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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {TYPE_1__* bus; } ;
struct hfi1_devdata {struct pci_dev* pcidev; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_L1_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 scalar_t__ is_ax (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool aspm_hw_l1_supported(struct hfi1_devdata *dd)
{
	struct pci_dev *parent = dd->pcidev->bus->self;
	u32 up, dn;

	/*
	 * If the driver does not have access to the upstream component,
	 * it cannot support ASPM L1 at all.
	 */
	if (!parent)
		return false;

	pcie_capability_read_dword(dd->pcidev, PCI_EXP_LNKCAP, &dn);
	dn = ASPM_L1_SUPPORTED(dn);

	pcie_capability_read_dword(parent, PCI_EXP_LNKCAP, &up);
	up = ASPM_L1_SUPPORTED(up);

	/* ASPM works on A-step but is reported as not supported */
	return (!!dn || is_ax(dd)) && !!up;
}