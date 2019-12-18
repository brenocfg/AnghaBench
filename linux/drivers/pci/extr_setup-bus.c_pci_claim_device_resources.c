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
struct resource {scalar_t__ parent; int /*<<< orphan*/  flags; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int PCI_BRIDGE_RESOURCES ; 
 int /*<<< orphan*/  pci_claim_resource (struct pci_dev*,int) ; 

__attribute__((used)) static void pci_claim_device_resources(struct pci_dev *dev)
{
	int i;

	for (i = 0; i < PCI_BRIDGE_RESOURCES; i++) {
		struct resource *r = &dev->resource[i];

		if (!r->flags || r->parent)
			continue;

		pci_claim_resource(dev, i);
	}
}