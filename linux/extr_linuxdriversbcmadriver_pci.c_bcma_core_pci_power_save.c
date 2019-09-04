#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct bcma_drv_pci {TYPE_2__* core; } ;
struct bcma_bus {scalar_t__ hosttype; struct bcma_drv_pci* drv_pci; } ;
struct TYPE_3__ {int rev; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCI_MDIO_BLK1 ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_MDIO_BLK1_MGMT1 ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_MDIO_BLK1_MGMT3 ; 
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int /*<<< orphan*/  bcma_pcie_mdio_writeread (struct bcma_drv_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void bcma_core_pci_power_save(struct bcma_bus *bus, bool up)
{
	struct bcma_drv_pci *pc;
	u16 data;

	if (bus->hosttype != BCMA_HOSTTYPE_PCI)
		return;

	pc = &bus->drv_pci[0];

	if (pc->core->id.rev >= 15 && pc->core->id.rev <= 20) {
		data = up ? 0x74 : 0x7C;
		bcma_pcie_mdio_writeread(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT1, 0x7F64);
		bcma_pcie_mdio_writeread(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT3, data);
	} else if (pc->core->id.rev >= 21 && pc->core->id.rev <= 22) {
		data = up ? 0x75 : 0x7D;
		bcma_pcie_mdio_writeread(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT1, 0x7E65);
		bcma_pcie_mdio_writeread(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT3, data);
	}
}