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
typedef  unsigned int u16 ;
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct pci_dev {int /*<<< orphan*/  bus; struct resource* resource; } ;
struct pci_bus_region {unsigned int start; unsigned int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  pci_claim_resource (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,struct resource*,char const*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,unsigned int*) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (int /*<<< orphan*/ ,struct resource*,struct pci_bus_region*) ; 

__attribute__((used)) static void quirk_io_region(struct pci_dev *dev, int port,
				unsigned size, int nr, const char *name)
{
	u16 region;
	struct pci_bus_region bus_region;
	struct resource *res = dev->resource + nr;

	pci_read_config_word(dev, port, &region);
	region &= ~(size - 1);

	if (!region)
		return;

	res->name = pci_name(dev);
	res->flags = IORESOURCE_IO;

	/* Convert from PCI bus to resource space */
	bus_region.start = region;
	bus_region.end = region + size - 1;
	pcibios_bus_to_resource(dev->bus, res, &bus_region);

	if (!pci_claim_resource(dev, nr))
		pci_info(dev, "quirk: %pR claimed by %s\n", res, name);
}