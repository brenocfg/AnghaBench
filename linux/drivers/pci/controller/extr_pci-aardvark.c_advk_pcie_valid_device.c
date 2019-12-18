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
struct pci_bus {scalar_t__ number; } ;
struct advk_pcie {scalar_t__ root_bus_nr; } ;

/* Variables and functions */
 scalar_t__ PCI_SLOT (int) ; 

__attribute__((used)) static bool advk_pcie_valid_device(struct advk_pcie *pcie, struct pci_bus *bus,
				  int devfn)
{
	if ((bus->number == pcie->root_bus_nr) && PCI_SLOT(devfn) != 0)
		return false;

	return true;
}