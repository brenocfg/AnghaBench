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
struct dce_abm_shift {int dummy; } ;
struct dce_abm_registers {int dummy; } ;
struct dce_abm_mask {int dummy; } ;
struct abm {int /*<<< orphan*/ * funcs; } ;
struct dce_abm {struct abm base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dce_abm_construct (struct dce_abm*,struct dc_context*,struct dce_abm_registers const*,struct dce_abm_shift const*,struct dce_abm_mask const*) ; 
 int /*<<< orphan*/  dce_funcs ; 
 struct dce_abm* kzalloc (int,int /*<<< orphan*/ ) ; 

struct abm *dce_abm_create(
	struct dc_context *ctx,
	const struct dce_abm_registers *regs,
	const struct dce_abm_shift *abm_shift,
	const struct dce_abm_mask *abm_mask)
{
	struct dce_abm *abm_dce = kzalloc(sizeof(*abm_dce), GFP_KERNEL);

	if (abm_dce == NULL) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	dce_abm_construct(abm_dce, ctx, regs, abm_shift, abm_mask);

	abm_dce->base.funcs = &dce_funcs;

	return &abm_dce->base;
}