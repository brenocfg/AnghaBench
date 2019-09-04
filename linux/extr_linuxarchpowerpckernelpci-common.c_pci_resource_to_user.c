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
struct resource {int flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_bus_region {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,struct resource*) ; 

void pci_resource_to_user(const struct pci_dev *dev, int bar,
			  const struct resource *rsrc,
			  resource_size_t *start, resource_size_t *end)
{
	struct pci_bus_region region;

	if (rsrc->flags & IORESOURCE_IO) {
		pcibios_resource_to_bus(dev->bus, &region,
					(struct resource *) rsrc);
		*start = region.start;
		*end = region.end;
		return;
	}

	/* We pass a CPU physical address to userland for MMIO instead of a
	 * BAR value because X is lame and expects to be able to use that
	 * to pass to /dev/mem!
	 *
	 * That means we may have 64-bit values where some apps only expect
	 * 32 (like X itself since it thinks only Sparc has 64-bit MMIO).
	 */
	*start = rsrc->start;
	*end = rsrc->end;
}