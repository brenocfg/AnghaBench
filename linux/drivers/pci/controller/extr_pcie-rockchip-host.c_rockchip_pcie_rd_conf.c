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
struct rockchip_pcie {scalar_t__ root_bus_nr; } ;
struct pci_bus {scalar_t__ number; struct rockchip_pcie* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int rockchip_pcie_rd_other_conf (struct rockchip_pcie*,struct pci_bus*,int,int,int,int*) ; 
 int rockchip_pcie_rd_own_conf (struct rockchip_pcie*,int,int,int*) ; 
 int /*<<< orphan*/  rockchip_pcie_valid_device (struct rockchip_pcie*,struct pci_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_pcie_rd_conf(struct pci_bus *bus, u32 devfn, int where,
				 int size, u32 *val)
{
	struct rockchip_pcie *rockchip = bus->sysdata;

	if (!rockchip_pcie_valid_device(rockchip, bus, PCI_SLOT(devfn))) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (bus->number == rockchip->root_bus_nr)
		return rockchip_pcie_rd_own_conf(rockchip, where, size, val);

	return rockchip_pcie_rd_other_conf(rockchip, bus, devfn, where, size,
					   val);
}