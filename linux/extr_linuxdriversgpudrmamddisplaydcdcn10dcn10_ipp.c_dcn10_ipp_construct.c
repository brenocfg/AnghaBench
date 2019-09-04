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
struct dcn10_ipp_shift {int dummy; } ;
struct dcn10_ipp_registers {int dummy; } ;
struct dcn10_ipp_mask {int dummy; } ;
struct TYPE_2__ {int inst; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dcn10_ipp {struct dcn10_ipp_mask const* ipp_mask; struct dcn10_ipp_shift const* ipp_shift; struct dcn10_ipp_registers const* regs; TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_ipp_funcs ; 

void dcn10_ipp_construct(
	struct dcn10_ipp *ippn10,
	struct dc_context *ctx,
	int inst,
	const struct dcn10_ipp_registers *regs,
	const struct dcn10_ipp_shift *ipp_shift,
	const struct dcn10_ipp_mask *ipp_mask)
{
	ippn10->base.ctx = ctx;
	ippn10->base.inst = inst;
	ippn10->base.funcs = &dcn10_ipp_funcs;

	ippn10->regs = regs;
	ippn10->ipp_shift = ipp_shift;
	ippn10->ipp_mask = ipp_mask;
}