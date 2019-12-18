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
typedef  int /*<<< orphan*/  uint32_t ;
struct dcn_hubp2_shift {int dummy; } ;
struct dcn_hubp2_registers {int dummy; } ;
struct dcn_hubp2_mask {int dummy; } ;
struct TYPE_2__ {int mpcc_id; int /*<<< orphan*/  opp_id; int /*<<< orphan*/  inst; struct dc_context* ctx; int /*<<< orphan*/ * funcs; } ;
struct dcn21_hubp {TYPE_1__ base; struct dcn_hubp2_mask const* hubp_mask; struct dcn_hubp2_shift const* hubp_shift; struct dcn_hubp2_registers const* hubp_regs; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPP_ID_INVALID ; 
 int /*<<< orphan*/  dcn21_hubp_funcs ; 

bool hubp21_construct(
	struct dcn21_hubp *hubp21,
	struct dc_context *ctx,
	uint32_t inst,
	const struct dcn_hubp2_registers *hubp_regs,
	const struct dcn_hubp2_shift *hubp_shift,
	const struct dcn_hubp2_mask *hubp_mask)
{
	hubp21->base.funcs = &dcn21_hubp_funcs;
	hubp21->base.ctx = ctx;
	hubp21->hubp_regs = hubp_regs;
	hubp21->hubp_shift = hubp_shift;
	hubp21->hubp_mask = hubp_mask;
	hubp21->base.inst = inst;
	hubp21->base.opp_id = OPP_ID_INVALID;
	hubp21->base.mpcc_id = 0xf;

	return true;
}