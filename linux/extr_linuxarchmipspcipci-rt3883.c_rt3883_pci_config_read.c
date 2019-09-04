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
struct rt3883_pci_controller {int /*<<< orphan*/  pcie_ready; } ;
struct pci_bus {int number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  RT3883_PCI_REG_CFGADDR ; 
 int /*<<< orphan*/  RT3883_PCI_REG_CFGDATA ; 
 struct rt3883_pci_controller* pci_bus_to_rt3883_controller (struct pci_bus*) ; 
 int rt3883_pci_get_cfgaddr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rt3883_pci_r32 (struct rt3883_pci_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt3883_pci_w32 (struct rt3883_pci_controller*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt3883_pci_config_read(struct pci_bus *bus, unsigned int devfn,
				  int where, int size, u32 *val)
{
	struct rt3883_pci_controller *rpc;
	unsigned long flags;
	u32 address;
	u32 data;

	rpc = pci_bus_to_rt3883_controller(bus);

	if (!rpc->pcie_ready && bus->number == 1)
		return PCIBIOS_DEVICE_NOT_FOUND;

	address = rt3883_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					 PCI_FUNC(devfn), where);

	rt3883_pci_w32(rpc, address, RT3883_PCI_REG_CFGADDR);
	data = rt3883_pci_r32(rpc, RT3883_PCI_REG_CFGDATA);

	switch (size) {
	case 1:
		*val = (data >> ((where & 3) << 3)) & 0xff;
		break;
	case 2:
		*val = (data >> ((where & 3) << 3)) & 0xffff;
		break;
	case 4:
		*val = data;
		break;
	}

	return PCIBIOS_SUCCESSFUL;
}