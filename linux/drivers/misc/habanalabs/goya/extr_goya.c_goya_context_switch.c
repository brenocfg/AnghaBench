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
typedef  int u32 ;
struct asic_fixed_properties {int sram_base_address; int sram_size; } ;
struct hl_device {int /*<<< orphan*/  dev; scalar_t__ pldm; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int CFG_BASE ; 
 int NUMBER_OF_EXT_HW_QUEUES ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  goya_clear_sm_regs (struct hl_device*) ; 
 int goya_memset_device_memory (struct hl_device*,int,int,int,int) ; 
 int /*<<< orphan*/  goya_mmu_prepare (struct hl_device*,int) ; 
 int lower_32_bits (int) ; 
 int mmDMA_CH_0_WR_COMP_ADDR_LO ; 
 int mmDMA_CH_1_WR_COMP_ADDR_LO ; 
 int mmSYNC_MNGR_SOB_OBJ_1000 ; 
 int mmSYNC_MNGR_SOB_OBJ_1007 ; 
 int mmTPC_PLL_CLK_RLX_0 ; 

int goya_context_switch(struct hl_device *hdev, u32 asid)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u64 addr = prop->sram_base_address, sob_addr;
	u32 size = hdev->pldm ? 0x10000 : prop->sram_size;
	u64 val = 0x7777777777777777ull;
	int rc, dma_id;
	u32 channel_off = mmDMA_CH_1_WR_COMP_ADDR_LO -
					mmDMA_CH_0_WR_COMP_ADDR_LO;

	rc = goya_memset_device_memory(hdev, addr, size, val, false);
	if (rc) {
		dev_err(hdev->dev, "Failed to clear SRAM in context switch\n");
		return rc;
	}

	/* we need to reset registers that the user is allowed to change */
	sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1007;
	WREG32(mmDMA_CH_0_WR_COMP_ADDR_LO, lower_32_bits(sob_addr));

	for (dma_id = 1 ; dma_id < NUMBER_OF_EXT_HW_QUEUES ; dma_id++) {
		sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1000 +
							(dma_id - 1) * 4;
		WREG32(mmDMA_CH_0_WR_COMP_ADDR_LO + channel_off * dma_id,
						lower_32_bits(sob_addr));
	}

	WREG32(mmTPC_PLL_CLK_RLX_0, 0x200020);

	goya_mmu_prepare(hdev, asid);

	goya_clear_sm_regs(hdev);

	return 0;
}