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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct resource {int flags; } ;
struct pci_dev {int /*<<< orphan*/  bus; struct resource* resource; scalar_t__ io_window_1k; } ;
struct pci_bus_region {int start; int end; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int /*<<< orphan*/  PCI_BRIDGE_RESOURCES ; 
 unsigned long PCI_IO_1K_RANGE_MASK ; 
 int /*<<< orphan*/  PCI_IO_BASE ; 
 int /*<<< orphan*/  PCI_IO_BASE_UPPER16 ; 
 unsigned long PCI_IO_RANGE_MASK ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,struct resource*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,struct resource*) ; 

__attribute__((used)) static void pci_setup_bridge_io(struct pci_dev *bridge)
{
	struct resource *res;
	struct pci_bus_region region;
	unsigned long io_mask;
	u8 io_base_lo, io_limit_lo;
	u16 l;
	u32 io_upper16;

	io_mask = PCI_IO_RANGE_MASK;
	if (bridge->io_window_1k)
		io_mask = PCI_IO_1K_RANGE_MASK;

	/* Set up the top and bottom of the PCI I/O segment for this bus */
	res = &bridge->resource[PCI_BRIDGE_RESOURCES + 0];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	if (res->flags & IORESOURCE_IO) {
		pci_read_config_word(bridge, PCI_IO_BASE, &l);
		io_base_lo = (region.start >> 8) & io_mask;
		io_limit_lo = (region.end >> 8) & io_mask;
		l = ((u16) io_limit_lo << 8) | io_base_lo;
		/* Set up upper 16 bits of I/O base/limit */
		io_upper16 = (region.end & 0xffff0000) | (region.start >> 16);
		pci_info(bridge, "  bridge window %pR\n", res);
	} else {
		/* Clear upper 16 bits of I/O base/limit */
		io_upper16 = 0;
		l = 0x00f0;
	}
	/* Temporarily disable the I/O range before updating PCI_IO_BASE */
	pci_write_config_dword(bridge, PCI_IO_BASE_UPPER16, 0x0000ffff);
	/* Update lower 16 bits of I/O base/limit */
	pci_write_config_word(bridge, PCI_IO_BASE, l);
	/* Update upper 16 bits of I/O base/limit */
	pci_write_config_dword(bridge, PCI_IO_BASE_UPPER16, io_upper16);
}