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
typedef  int u64 ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (int /*<<< orphan*/ ) ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct acpi_device* acpi_find_child_device (int /*<<< orphan*/ ,int,int) ; 
 int pci_is_bridge (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct acpi_device *acpi_pci_find_companion(struct device *dev)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	bool check_children;
	u64 addr;

	check_children = pci_is_bridge(pci_dev);
	/* Please ref to ACPI spec for the syntax of _ADR */
	addr = (PCI_SLOT(pci_dev->devfn) << 16) | PCI_FUNC(pci_dev->devfn);
	return acpi_find_child_device(ACPI_COMPANION(dev->parent), addr,
				      check_children);
}