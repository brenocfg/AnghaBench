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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct resource {int /*<<< orphan*/  flags; } ;
struct pci_pbm_info {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_bus_region {int start; int end; } ;
struct pci_bus {struct resource** resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  APB_IO_ADDRESS_MAP ; 
 int /*<<< orphan*/  APB_MEM_ADDRESS_MAP ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  apb_calc_first_last (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (int /*<<< orphan*/ ,struct resource*,struct pci_bus_region*) ; 

__attribute__((used)) static void apb_fake_ranges(struct pci_dev *dev,
			    struct pci_bus *bus,
			    struct pci_pbm_info *pbm)
{
	struct pci_bus_region region;
	struct resource *res;
	u32 first, last;
	u8 map;

	pci_read_config_byte(dev, APB_IO_ADDRESS_MAP, &map);
	apb_calc_first_last(map, &first, &last);
	res = bus->resource[0];
	res->flags = IORESOURCE_IO;
	region.start = (first << 21);
	region.end = (last << 21) + ((1 << 21) - 1);
	pcibios_bus_to_resource(dev->bus, res, &region);

	pci_read_config_byte(dev, APB_MEM_ADDRESS_MAP, &map);
	apb_calc_first_last(map, &first, &last);
	res = bus->resource[1];
	res->flags = IORESOURCE_MEM;
	region.start = (first << 29);
	region.end = (last << 29) + ((1 << 29) - 1);
	pcibios_bus_to_resource(dev->bus, res, &region);
}