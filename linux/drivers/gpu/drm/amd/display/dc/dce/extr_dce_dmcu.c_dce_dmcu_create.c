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
struct dmcu {int /*<<< orphan*/ * funcs; } ;
struct dce_dmcu_shift {int dummy; } ;
struct dce_dmcu_registers {int dummy; } ;
struct dce_dmcu_mask {int dummy; } ;
struct dce_dmcu {struct dmcu base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dce_dmcu_construct (struct dce_dmcu*,struct dc_context*,struct dce_dmcu_registers const*,struct dce_dmcu_shift const*,struct dce_dmcu_mask const*) ; 
 int /*<<< orphan*/  dce_funcs ; 
 struct dce_dmcu* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dmcu *dce_dmcu_create(
	struct dc_context *ctx,
	const struct dce_dmcu_registers *regs,
	const struct dce_dmcu_shift *dmcu_shift,
	const struct dce_dmcu_mask *dmcu_mask)
{
	struct dce_dmcu *dmcu_dce = kzalloc(sizeof(*dmcu_dce), GFP_KERNEL);

	if (dmcu_dce == NULL) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	dce_dmcu_construct(
		dmcu_dce, ctx, regs, dmcu_shift, dmcu_mask);

	dmcu_dce->base.funcs = &dce_funcs;

	return &dmcu_dce->base;
}