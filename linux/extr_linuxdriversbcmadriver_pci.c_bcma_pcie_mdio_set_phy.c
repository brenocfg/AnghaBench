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
typedef  int u16 ;
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */
 int BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE ; 
 int BCMA_CORE_PCI_MDIODATA_BLK_ADDR ; 
 int BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF ; 
 int BCMA_CORE_PCI_MDIODATA_DEV_ADDR ; 
 int BCMA_CORE_PCI_MDIODATA_REGADDR_SHF ; 
 int BCMA_CORE_PCI_MDIODATA_START ; 
 int BCMA_CORE_PCI_MDIODATA_TA ; 
 int BCMA_CORE_PCI_MDIODATA_WRITE ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_MDIO_CONTROL ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_MDIO_DATA ; 
 int pcicore_read32 (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write32 (struct bcma_drv_pci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void bcma_pcie_mdio_set_phy(struct bcma_drv_pci *pc, u16 phy)
{
	u32 v;
	int i;

	v = BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_WRITE;
	v |= (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
	      BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
	v |= (BCMA_CORE_PCI_MDIODATA_BLK_ADDR <<
	      BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	v |= BCMA_CORE_PCI_MDIODATA_TA;
	v |= (phy << 4);
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_DATA, v);

	udelay(10);
	for (i = 0; i < 200; i++) {
		v = pcicore_read32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		if (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE)
			break;
		usleep_range(1000, 2000);
	}
}