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
struct dce_mem_input_shift {int dummy; } ;
struct dce_mem_input_registers {int dummy; } ;
struct dce_mem_input_mask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * funcs; } ;
struct dce_mem_input {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce120_mi_funcs ; 
 int /*<<< orphan*/  dce_mem_input_construct (struct dce_mem_input*,struct dc_context*,int,struct dce_mem_input_registers const*,struct dce_mem_input_shift const*,struct dce_mem_input_mask const*) ; 

void dce120_mem_input_construct(
	struct dce_mem_input *dce_mi,
	struct dc_context *ctx,
	int inst,
	const struct dce_mem_input_registers *regs,
	const struct dce_mem_input_shift *mi_shift,
	const struct dce_mem_input_mask *mi_mask)
{
	dce_mem_input_construct(dce_mi, ctx, inst, regs, mi_shift, mi_mask);
	dce_mi->base.funcs = &dce120_mi_funcs;
}