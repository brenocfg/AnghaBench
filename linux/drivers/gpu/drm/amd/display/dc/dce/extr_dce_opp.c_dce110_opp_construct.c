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
struct dce_opp_shift {int dummy; } ;
struct dce_opp_registers {int dummy; } ;
struct dce_opp_mask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inst; struct dc_context* ctx; int /*<<< orphan*/ * funcs; } ;
struct dce110_opp {struct dce_opp_mask const* opp_mask; struct dce_opp_shift const* opp_shift; struct dce_opp_registers const* regs; TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  funcs ; 

void dce110_opp_construct(struct dce110_opp *opp110,
	struct dc_context *ctx,
	uint32_t inst,
	const struct dce_opp_registers *regs,
	const struct dce_opp_shift *opp_shift,
	const struct dce_opp_mask *opp_mask)
{
	opp110->base.funcs = &funcs;

	opp110->base.ctx = ctx;

	opp110->base.inst = inst;

	opp110->regs = regs;
	opp110->opp_shift = opp_shift;
	opp110->opp_mask = opp_mask;
}