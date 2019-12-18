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
struct dce_ipp_shift {int dummy; } ;
struct dce_ipp_registers {int dummy; } ;
struct dce_ipp_mask {int dummy; } ;
struct TYPE_2__ {int inst; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_ipp {struct dce_ipp_mask const* ipp_mask; struct dce_ipp_shift const* ipp_shift; struct dce_ipp_registers const* regs; TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_ipp_funcs ; 

void dce_ipp_construct(
	struct dce_ipp *ipp_dce,
	struct dc_context *ctx,
	int inst,
	const struct dce_ipp_registers *regs,
	const struct dce_ipp_shift *ipp_shift,
	const struct dce_ipp_mask *ipp_mask)
{
	ipp_dce->base.ctx = ctx;
	ipp_dce->base.inst = inst;
	ipp_dce->base.funcs = &dce_ipp_funcs;

	ipp_dce->regs = regs;
	ipp_dce->ipp_shift = ipp_shift;
	ipp_dce->ipp_mask = ipp_mask;
}