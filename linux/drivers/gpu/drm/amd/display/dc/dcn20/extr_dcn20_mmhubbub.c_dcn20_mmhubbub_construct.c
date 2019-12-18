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
struct dcn20_mmhubbub_shift {int dummy; } ;
struct dcn20_mmhubbub_registers {int dummy; } ;
struct dcn20_mmhubbub_mask {int dummy; } ;
struct TYPE_2__ {int inst; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dcn20_mmhubbub {struct dcn20_mmhubbub_mask const* mcif_wb_mask; struct dcn20_mmhubbub_shift const* mcif_wb_shift; struct dcn20_mmhubbub_registers const* mcif_wb_regs; TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn20_mmhubbub_funcs ; 

void dcn20_mmhubbub_construct(struct dcn20_mmhubbub *mcif_wb20,
		struct dc_context *ctx,
		const struct dcn20_mmhubbub_registers *mcif_wb_regs,
		const struct dcn20_mmhubbub_shift *mcif_wb_shift,
		const struct dcn20_mmhubbub_mask *mcif_wb_mask,
		int inst)
{
	mcif_wb20->base.ctx = ctx;

	mcif_wb20->base.inst = inst;
	mcif_wb20->base.funcs = &dcn20_mmhubbub_funcs;

	mcif_wb20->mcif_wb_regs = mcif_wb_regs;
	mcif_wb20->mcif_wb_shift = mcif_wb_shift;
	mcif_wb20->mcif_wb_mask = mcif_wb_mask;
}