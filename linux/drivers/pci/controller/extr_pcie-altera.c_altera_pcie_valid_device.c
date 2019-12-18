#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_bus {scalar_t__ number; } ;
struct altera_pcie {scalar_t__ root_bus_nr; TYPE_2__* pcie_data; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_link_status ) (struct altera_pcie*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct altera_pcie*) ; 

__attribute__((used)) static bool altera_pcie_valid_device(struct altera_pcie *pcie,
				     struct pci_bus *bus, int dev)
{
	/* If there is no link, then there is no device */
	if (bus->number != pcie->root_bus_nr) {
		if (!pcie->pcie_data->ops->get_link_status(pcie))
			return false;
	}

	/* access only one slot on each root port */
	if (bus->number == pcie->root_bus_nr && dev > 0)
		return false;

	 return true;
}