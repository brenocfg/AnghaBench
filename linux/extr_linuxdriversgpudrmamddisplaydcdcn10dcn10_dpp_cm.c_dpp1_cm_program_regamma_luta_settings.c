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
struct xfer_func_reg {void* region_end; void* region_start; void* start_end_cntl2_r; void* start_end_cntl1_r; void* start_end_cntl2_g; void* start_end_cntl1_g; void* start_end_cntl2_b; void* start_end_cntl1_b; void* start_slope_cntl_r; void* start_slope_cntl_g; void* start_slope_cntl_b; void* start_cntl_r; void* start_cntl_g; void* start_cntl_b; } ;
struct pwl_params {int dummy; } ;
struct dpp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dcn10_dpp {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_RGAM_RAMA_END_CNTL1_B ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_END_CNTL1_G ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_END_CNTL1_R ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_END_CNTL2_B ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_END_CNTL2_G ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_END_CNTL2_R ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_REGION_0_1 ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_REGION_32_33 ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_SLOPE_CNTL_B ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_SLOPE_CNTL_G ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_SLOPE_CNTL_R ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_START_CNTL_B ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_START_CNTL_G ; 
 int /*<<< orphan*/  CM_RGAM_RAMA_START_CNTL_R ; 
 void* REG (int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 
 int /*<<< orphan*/  cm_helper_program_xfer_func (int /*<<< orphan*/ ,struct pwl_params const*,struct xfer_func_reg*) ; 
 int /*<<< orphan*/  dpp1_cm_get_reg_field (struct dcn10_dpp*,struct xfer_func_reg*) ; 

void dpp1_cm_program_regamma_luta_settings(
		struct dpp *dpp_base,
		const struct pwl_params *params)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	struct xfer_func_reg gam_regs;

	dpp1_cm_get_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_RGAM_RAMA_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_RGAM_RAMA_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_RGAM_RAMA_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_RGAM_RAMA_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_RGAM_RAMA_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_RGAM_RAMA_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_RGAM_RAMA_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_RGAM_RAMA_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_RGAM_RAMA_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_RGAM_RAMA_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_RGAM_RAMA_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_RGAM_RAMA_END_CNTL2_R);
	gam_regs.region_start = REG(CM_RGAM_RAMA_REGION_0_1);
	gam_regs.region_end = REG(CM_RGAM_RAMA_REGION_32_33);

	cm_helper_program_xfer_func(dpp->base.ctx, params, &gam_regs);

}