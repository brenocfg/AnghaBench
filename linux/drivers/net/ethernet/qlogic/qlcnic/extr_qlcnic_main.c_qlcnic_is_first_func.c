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
struct pci_dev {int devfn; scalar_t__ current_state; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ PCI_D3cold ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_is_first_func(struct pci_dev *pdev)
{
	struct pci_dev *oth_pdev;
	int val = pdev->devfn;

	while (val-- > 0) {
		oth_pdev = pci_get_domain_bus_and_slot(pci_domain_nr
			(pdev->bus), pdev->bus->number,
			PCI_DEVFN(PCI_SLOT(pdev->devfn), val));
		if (!oth_pdev)
			continue;

		if (oth_pdev->current_state != PCI_D3cold) {
			pci_dev_put(oth_pdev);
			return 0;
		}
		pci_dev_put(oth_pdev);
	}
	return 1;
}