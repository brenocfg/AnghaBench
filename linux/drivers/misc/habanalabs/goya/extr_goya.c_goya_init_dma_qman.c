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
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int GOYA_ASYNC_EVENT_ID_DMA0_QM ; 
 int /*<<< orphan*/  HL_QUEUE_LENGTH ; 
 int HW_CAP_MMU ; 
 int QMAN_DMA_ENABLE ; 
 int QMAN_DMA_ERR_MSG_EN ; 
 int QMAN_DMA_FULLY_TRUSTED ; 
 int QMAN_DMA_PARTLY_TRUSTED ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int lower_32_bits (scalar_t__) ; 
 int mmDMA_QM_0_CP_MSG_BASE0_ADDR_HI ; 
 int mmDMA_QM_0_CP_MSG_BASE0_ADDR_LO ; 
 int mmDMA_QM_0_CP_MSG_BASE1_ADDR_HI ; 
 int mmDMA_QM_0_CP_MSG_BASE1_ADDR_LO ; 
 int mmDMA_QM_0_CQ_CFG1 ; 
 int mmDMA_QM_0_GLBL_CFG0 ; 
 int mmDMA_QM_0_GLBL_ERR_ADDR_HI ; 
 int mmDMA_QM_0_GLBL_ERR_ADDR_LO ; 
 int mmDMA_QM_0_GLBL_ERR_CFG ; 
 int mmDMA_QM_0_GLBL_ERR_WDATA ; 
 int mmDMA_QM_0_GLBL_PROT ; 
 int mmDMA_QM_0_PQ_BASE_HI ; 
 int mmDMA_QM_0_PQ_BASE_LO ; 
 int mmDMA_QM_0_PQ_CFG1 ; 
 int mmDMA_QM_0_PQ_CI ; 
 int mmDMA_QM_0_PQ_PI ; 
 int mmDMA_QM_0_PQ_SIZE ; 
 int mmDMA_QM_1_PQ_PI ; 
 scalar_t__ mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 scalar_t__ mmSYNC_MNGR_MON_PAY_ADDRL_0 ; 
 scalar_t__ mmSYNC_MNGR_SOB_OBJ_0 ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void goya_init_dma_qman(struct hl_device *hdev, int dma_id,
		dma_addr_t bus_address)
{
	struct goya_device *goya = hdev->asic_specific;
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u32 reg_off = dma_id * (mmDMA_QM_1_PQ_PI - mmDMA_QM_0_PQ_PI);

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmDMA_QM_0_PQ_BASE_LO + reg_off, lower_32_bits(bus_address));
	WREG32(mmDMA_QM_0_PQ_BASE_HI + reg_off, upper_32_bits(bus_address));

	WREG32(mmDMA_QM_0_PQ_SIZE + reg_off, ilog2(HL_QUEUE_LENGTH));
	WREG32(mmDMA_QM_0_PQ_PI + reg_off, 0);
	WREG32(mmDMA_QM_0_PQ_CI + reg_off, 0);

	WREG32(mmDMA_QM_0_CP_MSG_BASE0_ADDR_LO + reg_off, mtr_base_lo);
	WREG32(mmDMA_QM_0_CP_MSG_BASE0_ADDR_HI + reg_off, mtr_base_hi);
	WREG32(mmDMA_QM_0_CP_MSG_BASE1_ADDR_LO + reg_off, so_base_lo);
	WREG32(mmDMA_QM_0_CP_MSG_BASE1_ADDR_HI + reg_off, so_base_hi);
	WREG32(mmDMA_QM_0_GLBL_ERR_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmDMA_QM_0_GLBL_ERR_ADDR_HI + reg_off, gic_base_hi);
	WREG32(mmDMA_QM_0_GLBL_ERR_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_DMA0_QM + dma_id);

	/* PQ has buffer of 2 cache lines, while CQ has 8 lines */
	WREG32(mmDMA_QM_0_PQ_CFG1 + reg_off, 0x00020002);
	WREG32(mmDMA_QM_0_CQ_CFG1 + reg_off, 0x00080008);

	if (goya->hw_cap_initialized & HW_CAP_MMU)
		WREG32(mmDMA_QM_0_GLBL_PROT + reg_off, QMAN_DMA_PARTLY_TRUSTED);
	else
		WREG32(mmDMA_QM_0_GLBL_PROT + reg_off, QMAN_DMA_FULLY_TRUSTED);

	WREG32(mmDMA_QM_0_GLBL_ERR_CFG + reg_off, QMAN_DMA_ERR_MSG_EN);
	WREG32(mmDMA_QM_0_GLBL_CFG0 + reg_off, QMAN_DMA_ENABLE);
}