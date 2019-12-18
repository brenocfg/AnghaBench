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
struct dcn20_dwbc_shift {int dummy; } ;
struct dcn20_dwbc_registers {int dummy; } ;
struct dcn20_dwbc_mask {int dummy; } ;
struct TYPE_2__ {int inst; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dcn20_dwbc {struct dcn20_dwbc_mask const* dwbc_mask; struct dcn20_dwbc_shift const* dwbc_shift; struct dcn20_dwbc_registers const* dwbc_regs; TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn20_dwbc_funcs ; 

void dcn20_dwbc_construct(struct dcn20_dwbc *dwbc20,
		struct dc_context *ctx,
		const struct dcn20_dwbc_registers *dwbc_regs,
		const struct dcn20_dwbc_shift *dwbc_shift,
		const struct dcn20_dwbc_mask *dwbc_mask,
		int inst)
{
	dwbc20->base.ctx = ctx;

	dwbc20->base.inst = inst;
	dwbc20->base.funcs = &dcn20_dwbc_funcs;

	dwbc20->dwbc_regs = dwbc_regs;
	dwbc20->dwbc_shift = dwbc_shift;
	dwbc20->dwbc_mask = dwbc_mask;
}