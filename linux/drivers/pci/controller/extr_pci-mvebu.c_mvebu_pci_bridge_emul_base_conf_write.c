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
typedef  int u32 ;
struct pci_bridge_emul_conf {int command; int /*<<< orphan*/  secondary_bus; int /*<<< orphan*/  iolimit; int /*<<< orphan*/  iobase; } ;
struct pci_bridge_emul {struct pci_bridge_emul_conf conf; struct mvebu_pcie_port* data; } ;
struct mvebu_pcie_port {int dummy; } ;

/* Variables and functions */
#define  PCI_COMMAND 132 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
#define  PCI_IO_BASE 131 
#define  PCI_IO_BASE_UPPER16 130 
 int /*<<< orphan*/  PCI_IO_RANGE_TYPE_32 ; 
#define  PCI_MEMORY_BASE 129 
#define  PCI_PRIMARY_BUS 128 
 int /*<<< orphan*/  mvebu_has_ioport (struct mvebu_pcie_port*) ; 
 int /*<<< orphan*/  mvebu_pcie_handle_iobase_change (struct mvebu_pcie_port*) ; 
 int /*<<< orphan*/  mvebu_pcie_handle_membase_change (struct mvebu_pcie_port*) ; 
 int /*<<< orphan*/  mvebu_pcie_set_local_bus_nr (struct mvebu_pcie_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvebu_pci_bridge_emul_base_conf_write(struct pci_bridge_emul *bridge,
				      int reg, u32 old, u32 new, u32 mask)
{
	struct mvebu_pcie_port *port = bridge->data;
	struct pci_bridge_emul_conf *conf = &bridge->conf;

	switch (reg) {
	case PCI_COMMAND:
	{
		if (!mvebu_has_ioport(port))
			conf->command &= ~PCI_COMMAND_IO;

		if ((old ^ new) & PCI_COMMAND_IO)
			mvebu_pcie_handle_iobase_change(port);
		if ((old ^ new) & PCI_COMMAND_MEMORY)
			mvebu_pcie_handle_membase_change(port);

		break;
	}

	case PCI_IO_BASE:
		/*
		 * We keep bit 1 set, it is a read-only bit that
		 * indicates we support 32 bits addressing for the
		 * I/O
		 */
		conf->iobase |= PCI_IO_RANGE_TYPE_32;
		conf->iolimit |= PCI_IO_RANGE_TYPE_32;
		mvebu_pcie_handle_iobase_change(port);
		break;

	case PCI_MEMORY_BASE:
		mvebu_pcie_handle_membase_change(port);
		break;

	case PCI_IO_BASE_UPPER16:
		mvebu_pcie_handle_iobase_change(port);
		break;

	case PCI_PRIMARY_BUS:
		mvebu_pcie_set_local_bus_nr(port, conf->secondary_bus);
		break;

	default:
		break;
	}
}