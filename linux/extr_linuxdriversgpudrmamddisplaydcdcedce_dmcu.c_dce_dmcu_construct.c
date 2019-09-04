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
struct dmcu {scalar_t__ cached_wait_loop_number; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_dmcu_shift {int dummy; } ;
struct dce_dmcu_registers {int dummy; } ;
struct dce_dmcu_mask {int dummy; } ;
struct dce_dmcu {struct dce_dmcu_mask const* dmcu_mask; struct dce_dmcu_shift const* dmcu_shift; struct dce_dmcu_registers const* regs; struct dmcu base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_funcs ; 

__attribute__((used)) static void dce_dmcu_construct(
	struct dce_dmcu *dmcu_dce,
	struct dc_context *ctx,
	const struct dce_dmcu_registers *regs,
	const struct dce_dmcu_shift *dmcu_shift,
	const struct dce_dmcu_mask *dmcu_mask)
{
	struct dmcu *base = &dmcu_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;
	base->cached_wait_loop_number = 0;

	dmcu_dce->regs = regs;
	dmcu_dce->dmcu_shift = dmcu_shift;
	dmcu_dce->dmcu_mask = dmcu_mask;
}