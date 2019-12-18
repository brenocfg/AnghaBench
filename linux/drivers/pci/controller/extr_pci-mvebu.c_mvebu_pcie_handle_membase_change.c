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
struct pci_bridge_emul_conf {int memlimit; int membase; int command; } ;
struct mvebu_pcie_window {int base; int size; int /*<<< orphan*/  remap; } ;
struct TYPE_2__ {struct pci_bridge_emul_conf conf; } ;
struct mvebu_pcie_port {int /*<<< orphan*/  memwin; int /*<<< orphan*/  mem_attr; int /*<<< orphan*/  mem_target; TYPE_1__ bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVEBU_MBUS_NO_REMAP ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  mvebu_pcie_set_window (struct mvebu_pcie_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mvebu_pcie_window*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvebu_pcie_handle_membase_change(struct mvebu_pcie_port *port)
{
	struct mvebu_pcie_window desired = {.remap = MVEBU_MBUS_NO_REMAP};
	struct pci_bridge_emul_conf *conf = &port->bridge.conf;

	/* Are the new membase/memlimit values invalid? */
	if (conf->memlimit < conf->membase ||
	    !(conf->command & PCI_COMMAND_MEMORY)) {
		mvebu_pcie_set_window(port, port->mem_target, port->mem_attr,
				      &desired, &port->memwin);
		return;
	}

	/*
	 * We read the PCI-to-PCI bridge emulated registers, and
	 * calculate the base address and size of the address decoding
	 * window to setup, according to the PCI-to-PCI bridge
	 * specifications.
	 */
	desired.base = ((conf->membase & 0xFFF0) << 16);
	desired.size = (((conf->memlimit & 0xFFF0) << 16) | 0xFFFFF) -
		       desired.base + 1;

	mvebu_pcie_set_window(port, port->mem_target, port->mem_attr, &desired,
			      &port->memwin);
}