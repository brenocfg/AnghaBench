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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int GOYA_ASYNC_EVENT_ID_DMA0_CH ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int lower_32_bits (scalar_t__) ; 
 int mmDMA_CH_0_CFG1 ; 
 int mmDMA_CH_0_ERRMSG_ADDR_HI ; 
 int mmDMA_CH_0_ERRMSG_ADDR_LO ; 
 int mmDMA_CH_0_ERRMSG_WDATA ; 
 int mmDMA_CH_0_WR_COMP_ADDR_HI ; 
 int mmDMA_CH_0_WR_COMP_WDATA ; 
 int mmDMA_CH_1_CFG1 ; 
 scalar_t__ mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 scalar_t__ mmSYNC_MNGR_SOB_OBJ_1000 ; 
 scalar_t__ mmSYNC_MNGR_SOB_OBJ_1007 ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void goya_init_dma_ch(struct hl_device *hdev, int dma_id)
{
	u32 gic_base_lo, gic_base_hi;
	u64 sob_addr;
	u32 reg_off = dma_id * (mmDMA_CH_1_CFG1 - mmDMA_CH_0_CFG1);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmDMA_CH_0_ERRMSG_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmDMA_CH_0_ERRMSG_ADDR_HI + reg_off, gic_base_hi);
	WREG32(mmDMA_CH_0_ERRMSG_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_DMA0_CH + dma_id);

	if (dma_id)
		sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1000 +
				(dma_id - 1) * 4;
	else
		sob_addr = CFG_BASE + mmSYNC_MNGR_SOB_OBJ_1007;

	WREG32(mmDMA_CH_0_WR_COMP_ADDR_HI + reg_off, upper_32_bits(sob_addr));
	WREG32(mmDMA_CH_0_WR_COMP_WDATA + reg_off, 0x80000001);
}