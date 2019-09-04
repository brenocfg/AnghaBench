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
struct resource {scalar_t__ start; int /*<<< orphan*/  end; scalar_t__ parent; int /*<<< orphan*/  flags; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 size_t PCI_ROM_RESOURCE ; 
 scalar_t__ pci_claim_resource (struct pci_dev*,size_t) ; 

__attribute__((used)) static void pcibios_allocate_dev_rom_resource(struct pci_dev *dev)
{
	struct resource *r;

	/*
	 * Try to use BIOS settings for ROMs, otherwise let
	 * pci_assign_unassigned_resources() allocate the new
	 * addresses.
	 */
	r = &dev->resource[PCI_ROM_RESOURCE];
	if (!r->flags || !r->start)
		return;
	if (r->parent) /* Already allocated */
		return;

	if (pci_claim_resource(dev, PCI_ROM_RESOURCE) < 0) {
		r->end -= r->start;
		r->start = 0;
	}
}