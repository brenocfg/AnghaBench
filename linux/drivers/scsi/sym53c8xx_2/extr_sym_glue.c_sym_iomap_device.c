#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* ramaddr; void* ioaddr; } ;
struct TYPE_4__ {int features; } ;
struct sym_device {int /*<<< orphan*/  ram_base; TYPE_2__ s; int /*<<< orphan*/  mmio_base; TYPE_1__ chip; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_3__* resource; int /*<<< orphan*/  bus; } ;
struct pci_bus_region {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EIO ; 
 int FE_RAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,TYPE_3__*) ; 

__attribute__((used)) static int sym_iomap_device(struct sym_device *device)
{
	struct pci_dev *pdev = device->pdev;
	struct pci_bus_region bus_addr;
	int i = 2;

	pcibios_resource_to_bus(pdev->bus, &bus_addr, &pdev->resource[1]);
	device->mmio_base = bus_addr.start;

	if (device->chip.features & FE_RAM) {
		/*
		 * If the BAR is 64-bit, resource 2 will be occupied by the
		 * upper 32 bits
		 */
		if (!pdev->resource[i].flags)
			i++;
		pcibios_resource_to_bus(pdev->bus, &bus_addr,
					&pdev->resource[i]);
		device->ram_base = bus_addr.start;
	}

#ifdef CONFIG_SCSI_SYM53C8XX_MMIO
	if (device->mmio_base)
		device->s.ioaddr = pci_iomap(pdev, 1,
						pci_resource_len(pdev, 1));
#endif
	if (!device->s.ioaddr)
		device->s.ioaddr = pci_iomap(pdev, 0,
						pci_resource_len(pdev, 0));
	if (!device->s.ioaddr) {
		dev_err(&pdev->dev, "could not map registers; giving up.\n");
		return -EIO;
	}
	if (device->ram_base) {
		device->s.ramaddr = pci_iomap(pdev, i,
						pci_resource_len(pdev, i));
		if (!device->s.ramaddr) {
			dev_warn(&pdev->dev,
				"could not map SRAM; continuing anyway.\n");
			device->ram_base = 0;
		}
	}

	return 0;
}