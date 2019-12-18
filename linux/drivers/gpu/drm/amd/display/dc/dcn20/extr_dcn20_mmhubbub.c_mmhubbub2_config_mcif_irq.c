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
struct mcif_wb {int dummy; } ;
struct mcif_irq_params {int /*<<< orphan*/  vce_slice_int_en; int /*<<< orphan*/  vce_int_en; int /*<<< orphan*/  sw_overrun_int_en; int /*<<< orphan*/  sw_slice_int_en; int /*<<< orphan*/  sw_int_en; } ;
struct dcn20_mmhubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_INT_EN ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_OVERRUN_INT_EN ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_SLICE_INT_EN ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_VCE_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_VCE_INT_EN ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_VCE_SLICE_INT_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_mmhubbub* TO_DCN20_MMHUBBUB (struct mcif_wb*) ; 

void mmhubbub2_config_mcif_irq(struct mcif_wb *mcif_wb,
		struct mcif_irq_params *params)
{
	struct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* Set interrupt mask */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_INT_EN, params->sw_int_en);
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_SLICE_INT_EN, params->sw_slice_int_en);
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_OVERRUN_INT_EN,  params->sw_overrun_int_en);

	REG_UPDATE(MCIF_WB_BUFMGR_VCE_CONTROL, MCIF_WB_BUFMGR_VCE_INT_EN,  params->vce_int_en);
	REG_UPDATE(MCIF_WB_BUFMGR_VCE_CONTROL, MCIF_WB_BUFMGR_VCE_SLICE_INT_EN,  params->vce_slice_int_en);
}