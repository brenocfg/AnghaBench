#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pci_dev {scalar_t__ cfg_size; scalar_t__ devfn; TYPE_1__* resource; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_PCI_FIXED ; 
 scalar_t__ PCIE_CAP_OFFSET ; 
 scalar_t__ PCI_DEVFN (int,int) ; 
 int PCI_ROM_RESOURCE ; 
 unsigned long fixed_bar_cap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned long,scalar_t__*) ; 
 int /*<<< orphan*/  pci_soc_mode ; 

__attribute__((used)) static void pci_fixed_bar_fixup(struct pci_dev *dev)
{
	unsigned long offset;
	u32 size;
	int i;

	if (!pci_soc_mode)
		return;

	/* Must have extended configuration space */
	if (dev->cfg_size < PCIE_CAP_OFFSET + 4)
		return;

	/* Fixup the BAR sizes for fixed BAR devices and make them unmoveable */
	offset = fixed_bar_cap(dev->bus, dev->devfn);
	if (!offset || PCI_DEVFN(2, 0) == dev->devfn ||
	    PCI_DEVFN(2, 2) == dev->devfn)
		return;

	for (i = 0; i < PCI_ROM_RESOURCE; i++) {
		pci_read_config_dword(dev, offset + 8 + (i * 4), &size);
		dev->resource[i].end = dev->resource[i].start + size - 1;
		dev->resource[i].flags |= IORESOURCE_PCI_FIXED;
	}
}