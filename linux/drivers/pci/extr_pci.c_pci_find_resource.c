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
struct resource {scalar_t__ start; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int PCI_ROM_RESOURCE ; 
 scalar_t__ resource_contains (struct resource*,struct resource*) ; 

struct resource *pci_find_resource(struct pci_dev *dev, struct resource *res)
{
	int i;

	for (i = 0; i < PCI_ROM_RESOURCE; i++) {
		struct resource *r = &dev->resource[i];

		if (r->start && resource_contains(r, res))
			return r;
	}

	return NULL;
}