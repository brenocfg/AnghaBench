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
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCI_PCIEIND_ADDR ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_PCIEIND_DATA ; 
 int /*<<< orphan*/  pcicore_read32 (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write32 (struct bcma_drv_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_pcie_write(struct bcma_drv_pci *pc, u32 address, u32 data)
{
	pcicore_write32(pc, BCMA_CORE_PCI_PCIEIND_ADDR, address);
	pcicore_read32(pc, BCMA_CORE_PCI_PCIEIND_ADDR);
	pcicore_write32(pc, BCMA_CORE_PCI_PCIEIND_DATA, data);
}