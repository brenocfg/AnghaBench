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
typedef  scalar_t__ u32 ;
struct rockchip_pcie {scalar_t__ root_bus_nr; scalar_t__ reg_base; } ;
struct pci_bus {TYPE_1__* parent; int /*<<< orphan*/  number; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_WRAPPER_TYPE0_CFG ; 
 int /*<<< orphan*/  AXI_WRAPPER_TYPE1_CFG ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCIE_ECAM_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_FUNC (scalar_t__) ; 
 int /*<<< orphan*/  PCI_SLOT (scalar_t__) ; 
 scalar_t__ readb (scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ readw (scalar_t__) ; 
 int /*<<< orphan*/  rockchip_pcie_cfg_configuration_accesses (struct rockchip_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_pcie_rd_other_conf(struct rockchip_pcie *rockchip,
				       struct pci_bus *bus, u32 devfn,
				       int where, int size, u32 *val)
{
	u32 busdev;

	busdev = PCIE_ECAM_ADDR(bus->number, PCI_SLOT(devfn),
				PCI_FUNC(devfn), where);

	if (!IS_ALIGNED(busdev, size)) {
		*val = 0;
		return PCIBIOS_BAD_REGISTER_NUMBER;
	}

	if (bus->parent->number == rockchip->root_bus_nr)
		rockchip_pcie_cfg_configuration_accesses(rockchip,
						AXI_WRAPPER_TYPE0_CFG);
	else
		rockchip_pcie_cfg_configuration_accesses(rockchip,
						AXI_WRAPPER_TYPE1_CFG);

	if (size == 4) {
		*val = readl(rockchip->reg_base + busdev);
	} else if (size == 2) {
		*val = readw(rockchip->reg_base + busdev);
	} else if (size == 1) {
		*val = readb(rockchip->reg_base + busdev);
	} else {
		*val = 0;
		return PCIBIOS_BAD_REGISTER_NUMBER;
	}
	return PCIBIOS_SUCCESSFUL;
}