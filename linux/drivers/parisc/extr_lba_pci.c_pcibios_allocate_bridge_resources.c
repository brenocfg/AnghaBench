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
struct resource {scalar_t__ flags; scalar_t__ end; scalar_t__ start; scalar_t__ parent; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int PCI_BRIDGE_RESOURCES ; 
 int PCI_NUM_RESOURCES ; 
 scalar_t__ pci_claim_bridge_resource (struct pci_dev*,int) ; 

__attribute__((used)) static void pcibios_allocate_bridge_resources(struct pci_dev *dev)
{
	int idx;
	struct resource *r;

	for (idx = PCI_BRIDGE_RESOURCES; idx < PCI_NUM_RESOURCES; idx++) {
		r = &dev->resource[idx];
		if (!r->flags)
			continue;
		if (r->parent)	/* Already allocated */
			continue;
		if (!r->start || pci_claim_bridge_resource(dev, idx) < 0) {
			/*
			 * Something is wrong with the region.
			 * Invalidate the resource to prevent
			 * child resource allocations in this
			 * range.
			 */
			r->start = r->end = 0;
			r->flags = 0;
		}
	}
}