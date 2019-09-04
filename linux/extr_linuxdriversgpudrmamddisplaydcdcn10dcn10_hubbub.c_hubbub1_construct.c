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
struct hubbub {int debug_test_index_pstate; struct dcn_hubbub_mask const* masks; struct dcn_hubbub_shift const* shifts; struct dcn_hubbub_registers const* regs; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dcn_hubbub_shift {int dummy; } ;
struct dcn_hubbub_registers {int dummy; } ;
struct dcn_hubbub_mask {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hubbub1_funcs ; 

void hubbub1_construct(struct hubbub *hubbub,
	struct dc_context *ctx,
	const struct dcn_hubbub_registers *hubbub_regs,
	const struct dcn_hubbub_shift *hubbub_shift,
	const struct dcn_hubbub_mask *hubbub_mask)
{
	hubbub->ctx = ctx;

	hubbub->funcs = &hubbub1_funcs;

	hubbub->regs = hubbub_regs;
	hubbub->shifts = hubbub_shift;
	hubbub->masks = hubbub_mask;

	hubbub->debug_test_index_pstate = 0x7;
}