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
struct pci_bus {scalar_t__ number; struct nwl_pcie* sysdata; } ;
struct nwl_pcie {scalar_t__ root_busno; } ;

/* Variables and functions */
 int /*<<< orphan*/  nwl_pcie_link_up (struct nwl_pcie*) ; 

__attribute__((used)) static bool nwl_pcie_valid_device(struct pci_bus *bus, unsigned int devfn)
{
	struct nwl_pcie *pcie = bus->sysdata;

	/* Check link before accessing downstream ports */
	if (bus->number != pcie->root_busno) {
		if (!nwl_pcie_link_up(pcie))
			return false;
	}

	/* Only one device down on each root port */
	if (bus->number == pcie->root_busno && devfn > 0)
		return false;

	return true;
}