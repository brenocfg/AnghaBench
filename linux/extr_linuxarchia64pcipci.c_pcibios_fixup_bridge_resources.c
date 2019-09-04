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
struct resource {int /*<<< orphan*/  start; scalar_t__ parent; int /*<<< orphan*/  flags; } ;
struct pci_dev {struct resource* resource; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int PCI_BRIDGE_RESOURCES ; 
 int PCI_NUM_RESOURCES ; 
 int /*<<< orphan*/  pci_claim_bridge_resource (struct pci_dev*,int) ; 

__attribute__((used)) static void pcibios_fixup_bridge_resources(struct pci_dev *dev)
{
	int idx;

	if (!dev->bus)
		return;

	for (idx = PCI_BRIDGE_RESOURCES; idx < PCI_NUM_RESOURCES; idx++) {
		struct resource *r = &dev->resource[idx];

		if (!r->flags || r->parent || !r->start)
			continue;

		pci_claim_bridge_resource(dev, idx);
	}
}