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
struct pci_dev {int class; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_PCI ; 
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 scalar_t__ pci_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_bridge_bases (struct pci_bus*) ; 

void pcibios_fixup_bus(struct pci_bus *bus)
{
	struct pci_dev *dev = bus->self;

	if (pci_has_flag(PCI_PROBE_ONLY) && dev &&
	    (dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) {
		pci_read_bridge_bases(bus);
	}
}