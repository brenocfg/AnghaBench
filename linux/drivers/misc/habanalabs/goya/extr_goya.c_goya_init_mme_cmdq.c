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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ sram_base_address; } ;
struct hl_device {TYPE_1__ asic_prop; } ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int CMDQ_MME_ENABLE ; 
 int CMDQ_MME_ERR_MSG_EN ; 
 int CMDQ_MME_ERR_PROT ; 
 int GOYA_ASYNC_EVENT_ID_MME_CMDQ ; 
 scalar_t__ MME_QMAN_BASE_OFFSET ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (scalar_t__) ; 
 scalar_t__ mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 int /*<<< orphan*/  mmMME_CMDQ_CP_MSG_BASE0_ADDR_HI ; 
 int /*<<< orphan*/  mmMME_CMDQ_CP_MSG_BASE0_ADDR_LO ; 
 int /*<<< orphan*/  mmMME_CMDQ_CP_MSG_BASE1_ADDR_HI ; 
 int /*<<< orphan*/  mmMME_CMDQ_CP_MSG_BASE1_ADDR_LO ; 
 int /*<<< orphan*/  mmMME_CMDQ_CQ_CFG1 ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_CFG0 ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_ERR_ADDR_HI ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_ERR_ADDR_LO ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_ERR_CFG ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_ERR_WDATA ; 
 int /*<<< orphan*/  mmMME_CMDQ_GLBL_PROT ; 
 scalar_t__ mmSYNC_MNGR_MON_PAY_ADDRL_0 ; 
 scalar_t__ mmSYNC_MNGR_SOB_OBJ_0 ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void goya_init_mme_cmdq(struct hl_device *hdev)
{
	u32 mtr_base_lo, mtr_base_hi;
	u32 so_base_lo, so_base_hi;
	u32 gic_base_lo, gic_base_hi;
	u64 qman_base_addr;

	mtr_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	mtr_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_MON_PAY_ADDRL_0);
	so_base_lo = lower_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);
	so_base_hi = upper_32_bits(CFG_BASE + mmSYNC_MNGR_SOB_OBJ_0);

	gic_base_lo =
		lower_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);
	gic_base_hi =
		upper_32_bits(CFG_BASE + mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR);

	qman_base_addr = hdev->asic_prop.sram_base_address +
				MME_QMAN_BASE_OFFSET;

	WREG32(mmMME_CMDQ_CP_MSG_BASE0_ADDR_LO, mtr_base_lo);
	WREG32(mmMME_CMDQ_CP_MSG_BASE0_ADDR_HI, mtr_base_hi);
	WREG32(mmMME_CMDQ_CP_MSG_BASE1_ADDR_LO,	so_base_lo);
	WREG32(mmMME_CMDQ_CP_MSG_BASE1_ADDR_HI, so_base_hi);

	/* CMDQ CQ has 20 cache lines */
	WREG32(mmMME_CMDQ_CQ_CFG1, 0x00140014);

	WREG32(mmMME_CMDQ_GLBL_ERR_ADDR_LO, gic_base_lo);
	WREG32(mmMME_CMDQ_GLBL_ERR_ADDR_HI, gic_base_hi);

	WREG32(mmMME_CMDQ_GLBL_ERR_WDATA, GOYA_ASYNC_EVENT_ID_MME_CMDQ);

	WREG32(mmMME_CMDQ_GLBL_ERR_CFG, CMDQ_MME_ERR_MSG_EN);

	WREG32(mmMME_CMDQ_GLBL_PROT, CMDQ_MME_ERR_PROT);

	WREG32(mmMME_CMDQ_GLBL_CFG0, CMDQ_MME_ENABLE);
}