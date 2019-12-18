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
struct hl_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int CMDQ_TPC_ENABLE ; 
 int CMDQ_TPC_ERR_MSG_EN ; 
 int CMDQ_TPC_ERR_PROT ; 
 int GOYA_ASYNC_EVENT_ID_TPC0_CMDQ ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int lower_32_bits (scalar_t__) ; 
 scalar_t__ mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 scalar_t__ mmSYNC_MNGR_MON_PAY_ADDRL_0 ; 
 scalar_t__ mmSYNC_MNGR_SOB_OBJ_0 ; 
 int mmTPC0_CMDQ_CP_MSG_BASE0_ADDR_HI ; 
 int mmTPC0_CMDQ_CP_MSG_BASE0_ADDR_LO ; 
 int mmTPC0_CMDQ_CP_MSG_BASE1_ADDR_HI ; 
 int mmTPC0_CMDQ_CP_MSG_BASE1_ADDR_LO ; 
 int mmTPC0_CMDQ_CQ_CFG1 ; 
 int mmTPC0_CMDQ_GLBL_CFG0 ; 
 int mmTPC0_CMDQ_GLBL_ERR_ADDR_HI ; 
 int mmTPC0_CMDQ_GLBL_ERR_ADDR_LO ; 
 int mmTPC0_CMDQ_GLBL_ERR_CFG ; 
 int mmTPC0_CMDQ_GLBL_ERR_WDATA ; 
 int mmTPC0_CMDQ_GLBL_PROT ; 
 int mmTPC1_CMDQ_CQ_CFG1 ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void goya_init_tpc_cmdq(struct hl_device *hdev, int tpc_id)
{
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u32 reg_off = tpc_id * (mmTPC1_CMDQ_CQ_CFG1 - mmTPC0_CMDQ_CQ_CFG1);

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	WREG32(mmTPC0_CMDQ_CP_MSG_BASE0_ADDR_LO + reg_off, mtr_base_lo);
	WREG32(mmTPC0_CMDQ_CP_MSG_BASE0_ADDR_HI + reg_off, mtr_base_hi);
	WREG32(mmTPC0_CMDQ_CP_MSG_BASE1_ADDR_LO + reg_off, so_base_lo);
	WREG32(mmTPC0_CMDQ_CP_MSG_BASE1_ADDR_HI + reg_off, so_base_hi);

	WREG32(mmTPC0_CMDQ_CQ_CFG1 + reg_off, 0x00140014);

	WREG32(mmTPC0_CMDQ_GLBL_ERR_ADDR_LO + reg_off, gic_base_lo);
	WREG32(mmTPC0_CMDQ_GLBL_ERR_ADDR_HI + reg_off, gic_base_hi);

	WREG32(mmTPC0_CMDQ_GLBL_ERR_WDATA + reg_off,
			GOYA_ASYNC_EVENT_ID_TPC0_CMDQ + tpc_id);

	WREG32(mmTPC0_CMDQ_GLBL_ERR_CFG + reg_off, CMDQ_TPC_ERR_MSG_EN);

	WREG32(mmTPC0_CMDQ_GLBL_PROT + reg_off, CMDQ_TPC_ERR_PROT);

	WREG32(mmTPC0_CMDQ_GLBL_CFG0 + reg_off, CMDQ_TPC_ENABLE);
}