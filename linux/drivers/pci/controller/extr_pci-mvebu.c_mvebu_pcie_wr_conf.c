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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {scalar_t__ number; struct mvebu_pcie* sysdata; } ;
struct mvebu_pcie_port {int /*<<< orphan*/  bridge; } ;
struct mvebu_pcie {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 struct mvebu_pcie_port* mvebu_pcie_find_port (struct mvebu_pcie*,struct pci_bus*,int /*<<< orphan*/ ) ; 
 int mvebu_pcie_hw_wr_conf (struct mvebu_pcie_port*,struct pci_bus*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_pcie_link_up (struct mvebu_pcie_port*) ; 
 int pci_bridge_emul_conf_write (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvebu_pcie_wr_conf(struct pci_bus *bus, u32 devfn,
			      int where, int size, u32 val)
{
	struct mvebu_pcie *pcie = bus->sysdata;
	struct mvebu_pcie_port *port;
	int ret;

	port = mvebu_pcie_find_port(pcie, bus, devfn);
	if (!port)
		return PCIBIOS_DEVICE_NOT_FOUND;

	/* Access the emulated PCI-to-PCI bridge */
	if (bus->number == 0)
		return pci_bridge_emul_conf_write(&port->bridge, where,
						  size, val);

	if (!mvebu_pcie_link_up(port))
		return PCIBIOS_DEVICE_NOT_FOUND;

	/* Access the real PCIe interface */
	ret = mvebu_pcie_hw_wr_conf(port, bus, devfn,
				    where, size, val);

	return ret;
}