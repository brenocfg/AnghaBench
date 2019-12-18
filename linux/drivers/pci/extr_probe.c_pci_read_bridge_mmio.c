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
typedef  int u16 ;
struct resource {int flags; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_bus_region {unsigned long start; unsigned long end; } ;
struct pci_bus {struct resource** resource; struct pci_dev* self; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCI_MEMORY_BASE ; 
 int /*<<< orphan*/  PCI_MEMORY_LIMIT ; 
 unsigned long PCI_MEMORY_RANGE_MASK ; 
 int PCI_MEMORY_RANGE_TYPE_MASK ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,struct resource*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (int /*<<< orphan*/ ,struct resource*,struct pci_bus_region*) ; 

__attribute__((used)) static void pci_read_bridge_mmio(struct pci_bus *child)
{
	struct pci_dev *dev = child->self;
	u16 mem_base_lo, mem_limit_lo;
	unsigned long base, limit;
	struct pci_bus_region region;
	struct resource *res;

	res = child->resource[1];
	pci_read_config_word(dev, PCI_MEMORY_BASE, &mem_base_lo);
	pci_read_config_word(dev, PCI_MEMORY_LIMIT, &mem_limit_lo);
	base = ((unsigned long) mem_base_lo & PCI_MEMORY_RANGE_MASK) << 16;
	limit = ((unsigned long) mem_limit_lo & PCI_MEMORY_RANGE_MASK) << 16;
	if (base <= limit) {
		res->flags = (mem_base_lo & PCI_MEMORY_RANGE_TYPE_MASK) | IORESOURCE_MEM;
		region.start = base;
		region.end = limit + 0xfffff;
		pcibios_bus_to_resource(dev->bus, res, &region);
		pci_info(dev, "  bridge window %pR\n", res);
	}
}