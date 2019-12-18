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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {scalar_t__ vendor; int device; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_IDT ; 
 int pci_bus_generic_read_dev_vendor_id (struct pci_bus*,int,int /*<<< orphan*/ *,int) ; 
 int pci_idt_bus_quirk (struct pci_bus*,int,int /*<<< orphan*/ *,int) ; 

bool pci_bus_read_dev_vendor_id(struct pci_bus *bus, int devfn, u32 *l,
				int timeout)
{
#ifdef CONFIG_PCI_QUIRKS
	struct pci_dev *bridge = bus->self;

	/*
	 * Certain IDT switches have an issue where they improperly trigger
	 * ACS Source Validation errors on completions for config reads.
	 */
	if (bridge && bridge->vendor == PCI_VENDOR_ID_IDT &&
	    bridge->device == 0x80b5)
		return pci_idt_bus_quirk(bus, devfn, l, timeout);
#endif

	return pci_bus_generic_read_dev_vendor_id(bus, devfn, l, timeout);
}