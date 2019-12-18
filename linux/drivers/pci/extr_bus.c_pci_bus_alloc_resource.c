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
struct resource {int flags; } ;
struct pci_bus {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int IORESOURCE_MEM_64 ; 
 int /*<<< orphan*/  pci_32_bit ; 
 int /*<<< orphan*/  pci_64_bit ; 
 int pci_bus_alloc_from_region (struct pci_bus*,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/  (*) (void*,struct resource const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_high ; 

int pci_bus_alloc_resource(struct pci_bus *bus, struct resource *res,
		resource_size_t size, resource_size_t align,
		resource_size_t min, unsigned long type_mask,
		resource_size_t (*alignf)(void *,
					  const struct resource *,
					  resource_size_t,
					  resource_size_t),
		void *alignf_data)
{
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	int rc;

	if (res->flags & IORESOURCE_MEM_64) {
		rc = pci_bus_alloc_from_region(bus, res, size, align, min,
					       type_mask, alignf, alignf_data,
					       &pci_high);
		if (rc == 0)
			return 0;

		return pci_bus_alloc_from_region(bus, res, size, align, min,
						 type_mask, alignf, alignf_data,
						 &pci_64_bit);
	}
#endif

	return pci_bus_alloc_from_region(bus, res, size, align, min,
					 type_mask, alignf, alignf_data,
					 &pci_32_bit);
}