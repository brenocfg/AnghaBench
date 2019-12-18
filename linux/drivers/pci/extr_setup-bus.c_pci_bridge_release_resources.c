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
struct resource {unsigned long flags; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  parent; } ;
struct pci_dev {struct resource* resource; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM_64 ; 
 unsigned long IORESOURCE_PREFETCH ; 
 size_t PCI_BRIDGE_RESOURCES ; 
 unsigned int PCI_RES_TYPE_MASK ; 
 int /*<<< orphan*/  __pci_setup_bridge (struct pci_bus*,unsigned long) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,size_t,struct resource*) ; 
 int /*<<< orphan*/  release_child_resources (struct resource*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static void pci_bridge_release_resources(struct pci_bus *bus,
					 unsigned long type)
{
	struct pci_dev *dev = bus->self;
	struct resource *r;
	unsigned old_flags = 0;
	struct resource *b_res;
	int idx = 1;

	b_res = &dev->resource[PCI_BRIDGE_RESOURCES];

	/*
	 * 1. If IO port assignment fails, release bridge IO port.
	 * 2. If non pref MMIO assignment fails, release bridge nonpref MMIO.
	 * 3. If 64bit pref MMIO assignment fails, and bridge pref is 64bit,
	 *    release bridge pref MMIO.
	 * 4. If pref MMIO assignment fails, and bridge pref is 32bit,
	 *    release bridge pref MMIO.
	 * 5. If pref MMIO assignment fails, and bridge pref is not
	 *    assigned, release bridge nonpref MMIO.
	 */
	if (type & IORESOURCE_IO)
		idx = 0;
	else if (!(type & IORESOURCE_PREFETCH))
		idx = 1;
	else if ((type & IORESOURCE_MEM_64) &&
		 (b_res[2].flags & IORESOURCE_MEM_64))
		idx = 2;
	else if (!(b_res[2].flags & IORESOURCE_MEM_64) &&
		 (b_res[2].flags & IORESOURCE_PREFETCH))
		idx = 2;
	else
		idx = 1;

	r = &b_res[idx];

	if (!r->parent)
		return;

	/* If there are children, release them all */
	release_child_resources(r);
	if (!release_resource(r)) {
		type = old_flags = r->flags & PCI_RES_TYPE_MASK;
		pci_info(dev, "resource %d %pR released\n",
			 PCI_BRIDGE_RESOURCES + idx, r);
		/* Keep the old size */
		r->end = resource_size(r) - 1;
		r->start = 0;
		r->flags = 0;

		/* Avoiding touch the one without PREF */
		if (type & IORESOURCE_PREFETCH)
			type = IORESOURCE_PREFETCH;
		__pci_setup_bridge(bus, type);
		/* For next child res under same bridge */
		r->flags = old_flags;
	}
}