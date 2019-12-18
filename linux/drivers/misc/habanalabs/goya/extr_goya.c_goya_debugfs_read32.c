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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct asic_fixed_properties {int dram_size; int dram_pci_bar_size; } ;
struct hl_device {int* pcie_bar; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int CFG_BASE ; 
 int CFG_SIZE ; 
 size_t DDR_BAR_ID ; 
 int DRAM_PHYS_BASE ; 
 int EFAULT ; 
 int EIO ; 
 int HOST_PHYS_BASE ; 
 int /*<<< orphan*/  RREG32 (int) ; 
 int SRAM_BASE_ADDR ; 
 size_t SRAM_CFG_BAR_ID ; 
 int SRAM_SIZE ; 
 int U64_MAX ; 
 int goya_set_ddr_bar_base (struct hl_device*,int) ; 
 int /*<<< orphan*/  iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 scalar_t__ phys_to_virt (int) ; 
 int /*<<< orphan*/  readl (int) ; 

__attribute__((used)) static int goya_debugfs_read32(struct hl_device *hdev, u64 addr, u32 *val)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u64 ddr_bar_addr;
	int rc = 0;

	if ((addr >= CFG_BASE) && (addr < CFG_BASE + CFG_SIZE)) {
		*val = RREG32(addr - CFG_BASE);

	} else if ((addr >= SRAM_BASE_ADDR) &&
			(addr < SRAM_BASE_ADDR + SRAM_SIZE)) {

		*val = readl(hdev->pcie_bar[SRAM_CFG_BAR_ID] +
				(addr - SRAM_BASE_ADDR));

	} else if ((addr >= DRAM_PHYS_BASE) &&
			(addr < DRAM_PHYS_BASE + hdev->asic_prop.dram_size)) {

		u64 bar_base_addr = DRAM_PHYS_BASE +
				(addr & ~(prop->dram_pci_bar_size - 0x1ull));

		ddr_bar_addr = goya_set_ddr_bar_base(hdev, bar_base_addr);
		if (ddr_bar_addr != U64_MAX) {
			*val = readl(hdev->pcie_bar[DDR_BAR_ID] +
						(addr - bar_base_addr));

			ddr_bar_addr = goya_set_ddr_bar_base(hdev,
							ddr_bar_addr);
		}
		if (ddr_bar_addr == U64_MAX)
			rc = -EIO;

	} else if (addr >= HOST_PHYS_BASE && !iommu_present(&pci_bus_type)) {
		*val = *(u32 *) phys_to_virt(addr - HOST_PHYS_BASE);

	} else {
		rc = -EFAULT;
	}

	return rc;
}