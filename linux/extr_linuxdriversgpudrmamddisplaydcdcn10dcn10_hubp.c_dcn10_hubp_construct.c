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
struct dcn_mi_shift {int dummy; } ;
struct dcn_mi_registers {int dummy; } ;
struct dcn_mi_mask {int dummy; } ;
struct TYPE_2__ {int opp_id; int mpcc_id; int /*<<< orphan*/  inst; struct dc_context* ctx; int /*<<< orphan*/ * funcs; } ;
struct dcn10_hubp {TYPE_1__ base; struct dcn_mi_mask const* hubp_mask; struct dcn_mi_shift const* hubp_shift; struct dcn_mi_registers const* hubp_regs; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_hubp_funcs ; 

void dcn10_hubp_construct(
	struct dcn10_hubp *hubp1,
	struct dc_context *ctx,
	uint32_t inst,
	const struct dcn_mi_registers *hubp_regs,
	const struct dcn_mi_shift *hubp_shift,
	const struct dcn_mi_mask *hubp_mask)
{
	hubp1->base.funcs = &dcn10_hubp_funcs;
	hubp1->base.ctx = ctx;
	hubp1->hubp_regs = hubp_regs;
	hubp1->hubp_shift = hubp_shift;
	hubp1->hubp_mask = hubp_mask;
	hubp1->base.inst = inst;
	hubp1->base.opp_id = 0xf;
	hubp1->base.mpcc_id = 0xf;
}