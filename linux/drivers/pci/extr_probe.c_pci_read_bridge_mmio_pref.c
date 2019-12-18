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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct resource {int flags; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_bus_region {int start; int end; } ;
struct pci_bus {struct resource** resource; struct pci_dev* self; } ;
typedef  int pci_bus_addr_t ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_MEM_64 ; 
 int IORESOURCE_PREFETCH ; 
 int /*<<< orphan*/  PCI_PREF_BASE_UPPER32 ; 
 int /*<<< orphan*/  PCI_PREF_LIMIT_UPPER32 ; 
 int /*<<< orphan*/  PCI_PREF_MEMORY_BASE ; 
 int /*<<< orphan*/  PCI_PREF_MEMORY_LIMIT ; 
 int PCI_PREF_RANGE_MASK ; 
 int PCI_PREF_RANGE_TYPE_64 ; 
 int PCI_PREF_RANGE_TYPE_MASK ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,unsigned long long) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,struct resource*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (int /*<<< orphan*/ ,struct resource*,struct pci_bus_region*) ; 

__attribute__((used)) static void pci_read_bridge_mmio_pref(struct pci_bus *child)
{
	struct pci_dev *dev = child->self;
	u16 mem_base_lo, mem_limit_lo;
	u64 base64, limit64;
	pci_bus_addr_t base, limit;
	struct pci_bus_region region;
	struct resource *res;

	res = child->resource[2];
	pci_read_config_word(dev, PCI_PREF_MEMORY_BASE, &mem_base_lo);
	pci_read_config_word(dev, PCI_PREF_MEMORY_LIMIT, &mem_limit_lo);
	base64 = (mem_base_lo & PCI_PREF_RANGE_MASK) << 16;
	limit64 = (mem_limit_lo & PCI_PREF_RANGE_MASK) << 16;

	if ((mem_base_lo & PCI_PREF_RANGE_TYPE_MASK) == PCI_PREF_RANGE_TYPE_64) {
		u32 mem_base_hi, mem_limit_hi;

		pci_read_config_dword(dev, PCI_PREF_BASE_UPPER32, &mem_base_hi);
		pci_read_config_dword(dev, PCI_PREF_LIMIT_UPPER32, &mem_limit_hi);

		/*
		 * Some bridges set the base > limit by default, and some
		 * (broken) BIOSes do not initialize them.  If we find
		 * this, just assume they are not being used.
		 */
		if (mem_base_hi <= mem_limit_hi) {
			base64 |= (u64) mem_base_hi << 32;
			limit64 |= (u64) mem_limit_hi << 32;
		}
	}

	base = (pci_bus_addr_t) base64;
	limit = (pci_bus_addr_t) limit64;

	if (base != base64) {
		pci_err(dev, "can't handle bridge window above 4GB (bus address %#010llx)\n",
			(unsigned long long) base64);
		return;
	}

	if (base <= limit) {
		res->flags = (mem_base_lo & PCI_PREF_RANGE_TYPE_MASK) |
					 IORESOURCE_MEM | IORESOURCE_PREFETCH;
		if (res->flags & PCI_PREF_RANGE_TYPE_64)
			res->flags |= IORESOURCE_MEM_64;
		region.start = base;
		region.end = limit + 0xfffff;
		pcibios_bus_to_resource(dev->bus, res, &region);
		pci_info(dev, "  bridge window %pR\n", res);
	}
}