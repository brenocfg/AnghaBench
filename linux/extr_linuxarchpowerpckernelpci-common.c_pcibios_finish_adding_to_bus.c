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
struct pci_bus {scalar_t__ self; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 int /*<<< orphan*/  eeh_add_device_tree_late (struct pci_bus*) ; 
 int /*<<< orphan*/  eeh_add_sysfs_files (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_assign_unassigned_bridge_resources (scalar_t__) ; 
 int /*<<< orphan*/  pci_assign_unassigned_bus_resources (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_add_devices (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcibios_allocate_bus_resources (struct pci_bus*) ; 
 int /*<<< orphan*/  pcibios_claim_one_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pcibios_finish_adding_to_bus(struct pci_bus *bus)
{
	pr_debug("PCI: Finishing adding to hotplug bus %04x:%02x\n",
		 pci_domain_nr(bus), bus->number);

	/* Allocate bus and devices resources */
	pcibios_allocate_bus_resources(bus);
	pcibios_claim_one_bus(bus);
	if (!pci_has_flag(PCI_PROBE_ONLY)) {
		if (bus->self)
			pci_assign_unassigned_bridge_resources(bus->self);
		else
			pci_assign_unassigned_bus_resources(bus);
	}

	/* Fixup EEH */
	eeh_add_device_tree_late(bus);

	/* Add new devices to global lists.  Register in proc, sysfs. */
	pci_bus_add_devices(bus);

	/* sysfs files should only be added after devices are added */
	eeh_add_sysfs_files(bus);
}