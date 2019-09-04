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
struct pci_dev {struct pci_bus* bus; } ;
struct pci_bus {scalar_t__ number; struct pci_dev* self; struct pci_bus* parent; } ;

/* Variables and functions */
 scalar_t__ cpu_is_xlp9xx () ; 

struct pci_dev *xlp_get_pcie_link(const struct pci_dev *dev)
{
	struct pci_bus *bus, *p;

	bus = dev->bus;

	if (cpu_is_xlp9xx()) {
		/* find bus with grand parent number == 0 */
		for (p = bus->parent; p && p->parent && p->parent->number != 0;
				p = p->parent)
			bus = p;
		return (p && p->parent) ? bus->self : NULL;
	} else {
		/* Find the bridge on bus 0 */
		for (p = bus->parent; p && p->number != 0; p = p->parent)
			bus = p;

		return p ? bus->self : NULL;
	}
}