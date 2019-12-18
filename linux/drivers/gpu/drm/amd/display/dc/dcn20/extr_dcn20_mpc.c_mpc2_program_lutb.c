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
struct mpc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dcn20_mpc {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_END_CNTL1_B ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_END_CNTL1_G ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_END_CNTL1_R ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_END_CNTL2_B ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_END_CNTL2_G ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_END_CNTL2_R ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_REGION_0_1 ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_REGION_32_33 ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_SLOPE_CNTL_B ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_SLOPE_CNTL_G ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_SLOPE_CNTL_R ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_START_CNTL_B ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_START_CNTL_G ; 
 int /*<<< orphan*/ * MPCC_OGAM_RAMB_START_CNTL_R ; 
 void* REG (int /*<<< orphan*/ ) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 
 int /*<<< orphan*/  cm_helper_program_xfer_func (int /*<<< orphan*/ ,struct pwl_params const*,struct xfer_func_reg*) ; 
 int /*<<< orphan*/  mpc2_ogam_get_reg_field (struct mpc*,struct xfer_func_reg*) ; 

__attribute__((used)) static void mpc2_program_lutb(struct mpc *mpc, int mpcc_id,
			const struct pwl_params *params)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	struct xfer_func_reg gam_regs;

	mpc2_ogam_get_reg_field(mpc, &gam_regs);

	gam_regs.start_cntl_b = REG(MPCC_OGAM_RAMB_START_CNTL_B[mpcc_id]);
	gam_regs.start_cntl_g = REG(MPCC_OGAM_RAMB_START_CNTL_G[mpcc_id]);
	gam_regs.start_cntl_r = REG(MPCC_OGAM_RAMB_START_CNTL_R[mpcc_id]);
	gam_regs.start_slope_cntl_b = REG(MPCC_OGAM_RAMB_SLOPE_CNTL_B[mpcc_id]);
	gam_regs.start_slope_cntl_g = REG(MPCC_OGAM_RAMB_SLOPE_CNTL_G[mpcc_id]);
	gam_regs.start_slope_cntl_r = REG(MPCC_OGAM_RAMB_SLOPE_CNTL_R[mpcc_id]);
	gam_regs.start_end_cntl1_b = REG(MPCC_OGAM_RAMB_END_CNTL1_B[mpcc_id]);
	gam_regs.start_end_cntl2_b = REG(MPCC_OGAM_RAMB_END_CNTL2_B[mpcc_id]);
	gam_regs.start_end_cntl1_g = REG(MPCC_OGAM_RAMB_END_CNTL1_G[mpcc_id]);
	gam_regs.start_end_cntl2_g = REG(MPCC_OGAM_RAMB_END_CNTL2_G[mpcc_id]);
	gam_regs.start_end_cntl1_r = REG(MPCC_OGAM_RAMB_END_CNTL1_R[mpcc_id]);
	gam_regs.start_end_cntl2_r = REG(MPCC_OGAM_RAMB_END_CNTL2_R[mpcc_id]);
	gam_regs.region_start = REG(MPCC_OGAM_RAMB_REGION_0_1[mpcc_id]);
	gam_regs.region_end = REG(MPCC_OGAM_RAMB_REGION_32_33[mpcc_id]);

	cm_helper_program_xfer_func(mpc20->base.ctx, params, &gam_regs);

}