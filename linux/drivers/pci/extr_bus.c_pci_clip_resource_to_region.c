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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct pci_bus_region {scalar_t__ start; scalar_t__ end; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcibios_bus_to_resource (struct pci_bus*,struct resource*,struct pci_bus_region*) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (struct pci_bus*,struct pci_bus_region*,struct resource*) ; 

__attribute__((used)) static void pci_clip_resource_to_region(struct pci_bus *bus,
					struct resource *res,
					struct pci_bus_region *region)
{
	struct pci_bus_region r;

	pcibios_resource_to_bus(bus, &r, res);
	if (r.start < region->start)
		r.start = region->start;
	if (r.end > region->end)
		r.end = region->end;

	if (r.end < r.start)
		res->end = res->start - 1;
	else
		pcibios_bus_to_resource(bus, res, &r);
}