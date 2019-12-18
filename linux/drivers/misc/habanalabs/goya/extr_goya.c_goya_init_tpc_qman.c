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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int sram_base_address; } ;
struct hl_device {TYPE_1__ asic_prop; } ;

/* Variables and functions */
 int CFG_BASE ; 
 int GOYA_ASYNC_EVENT_ID_TPC0_QM ; 
 int QMAN_TPC_ENABLE ; 
 int QMAN_TPC_ERR_MSG_EN ; 
 int QMAN_TPC_ERR_PROT ; 
 int /*<<< orphan*/  TPC_QMAN_LENGTH ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int lower_32_bits (int) ; 
 int mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 int mmSYNC_MNGR_MON_PAY_ADDRL_0 ; 
 int mmSYNC_MNGR_SOB_OBJ_0 ; 
 int mmTPC0_QM_CP_LDMA_COMMIT_OFFSET ; 
 int mmTPC0_QM_CP_LDMA_SRC_BASE_HI_OFFSET ; 
 int mmTPC0_QM_CP_LDMA_SRC_BASE_LO_OFFSET ; 
 int mmTPC0_QM_CP_LDMA_TSIZE_OFFSET ; 
 int mmTPC0_QM_CP_MSG_BASE0_ADDR_HI ; 
 int mmTPC0_QM_CP_MSG_BASE0_ADDR_LO ; 
 int mmTPC0_QM_CP_MSG_BASE1_ADDR_HI ; 
 int mmTPC0_QM_CP_MSG_BASE1_ADDR_LO ; 
 int mmTPC0_QM_CQ_CFG1 ; 
 int mmTPC0_QM_GLBL_CFG0 ; 
 int mmTPC0_QM_GLBL_ERR_ADDR_HI ; 
 int mmTPC0_QM_GLBL_ERR_ADDR_LO ; 
 int mmTPC0_QM_GLBL_ERR_CFG ; 
 int mmTPC0_QM_GLBL_ERR_WDATA ; 
 int mmTPC0_QM_GLBL_PROT ; 
 int mmTPC0_QM_PQ_BASE_HI ; 
 int mmTPC0_QM_PQ_BASE_LO ; 
 int mmTPC0_QM_PQ_CI ; 
 int mmTPC0_QM_PQ_PI ; 
 int mmTPC0_QM_PQ_SIZE ; 
 int mmTPC1_QM_PQ_PI ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void goya_init_tpc_qman(struct hl_device *hdev, u32 base_off, int tpc_id)
{
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u64 qman_base_addr;
	u32 reg_off = tpc_id * (mmTPC1_QM_PQ_PI - mmTPC0_QM_PQ_PI);

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	qman_base_addr = hdev->asic_prop.sram_base_address + base_off;

	WREG32(mmTPC0_QM_PQ_BASE_LO + reg_off, lower_32_bits(qman_base_addr));
	WREG32(mmTPC0_QM_PQ_BASE_HI + reg_off, upper_32_bits(qman_base_addr));
	WREG32(mmTPC0_QM_PQ_SIZE + reg_off, ilog2(TPC_QMAN_LENGTH));
	WREG32(mmTPC0_QM_PQ_PI + reg_off, 0);
	WREG32(mmTPC0_QM_PQ_CI + reg_off, 0);
	WREG32(mmTPC0_QM_CP_LDMA_SRC_BASE_LO_OFFSET + reg_off, 0x10C0);
	WREG32(mmTPC0_QM_CP_LDMA_SRC_BASE_HI_OFFSET + reg_off, 0x10C4);
	WREG32(mmTPC0_QM_CP_LDMA_TSIZE_OFFSET + reg_off, 0x10C8);
	WREG32(mmTPC0_QM_CP_LDMA_COMMIT_OFFSET + reg_off, 0x10CC);

	WREG32(mmTPC0_QM_CP_MSG_BASE0_ADDR_LO + reg_off, mtr_base_lo);
	WREG32(mmTPC0_QM_CP_MSG_BASE0_ADDR_HI + reg_off, mtr_base_hi);
	WREG32(mmTPC0_QM_CP_MSG_BASE1_ADDR_LO + reg_off, so_base_lo);
	WREG32(mmTPC0_QM_CP_MSG_BASE1_ADDR_HI + reg_off, so_base_hi);

	WREG32(mmTPC0_QM_CQ_CFG1 + reg_off, 0x00080008);

	WREG32(mmTPC0_QM_GLBL_ERR_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmTPC0_QM_GLBL_ERR_ADDR_HI + reg_off, gic_base_hi);

	WREG32(mmTPC0_QM_GLBL_ERR_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_TPC0_QM + tpc_id);

	WREG32(mmTPC0_QM_GLBL_ERR_CFG + reg_off, QMAN_TPC_ERR_MSG_EN);

	WREG32(mmTPC0_QM_GLBL_PROT + reg_off, QMAN_TPC_ERR_PROT);

	WREG32(mmTPC0_QM_GLBL_CFG0 + reg_off, QMAN_TPC_ENABLE);
}