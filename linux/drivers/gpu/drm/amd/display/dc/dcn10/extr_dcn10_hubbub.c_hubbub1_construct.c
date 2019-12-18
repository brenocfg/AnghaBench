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
struct hubbub {int dummy; } ;
struct dcn_hubbub_shift {int dummy; } ;
struct dcn_hubbub_registers {int dummy; } ;
struct dcn_hubbub_mask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dcn10_hubbub {int debug_test_index_pstate; struct dcn_hubbub_mask const* masks; struct dcn_hubbub_shift const* shifts; struct dcn_hubbub_registers const* regs; TYPE_1__ base; } ;
struct dc_context {scalar_t__ dce_version; } ;

/* Variables and functions */
 scalar_t__ DCN_VERSION_1_01 ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  hubbub1_funcs ; 

void hubbub1_construct(struct hubbub *hubbub,
	struct dc_context *ctx,
	const struct dcn_hubbub_registers *hubbub_regs,
	const struct dcn_hubbub_shift *hubbub_shift,
	const struct dcn_hubbub_mask *hubbub_mask)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	hubbub1->base.ctx = ctx;

	hubbub1->base.funcs = &hubbub1_funcs;

	hubbub1->regs = hubbub_regs;
	hubbub1->shifts = hubbub_shift;
	hubbub1->masks = hubbub_mask;

	hubbub1->debug_test_index_pstate = 0x7;
	if (ctx->dce_version == DCN_VERSION_1_01)
		hubbub1->debug_test_index_pstate = 0xB;
}