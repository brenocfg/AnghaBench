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
typedef  void* uint32_t ;
struct dce110_aux_registers {int dummy; } ;
struct dc_context {int dummy; } ;
struct aux_engine {void* inst; int /*<<< orphan*/ * funcs; scalar_t__ max_defer_write_retry; scalar_t__ delay; struct dc_context* ctx; int /*<<< orphan*/ * ddc; } ;
struct aux_engine_dce110 {struct aux_engine base; struct dce110_aux_registers const* regs; void* timeout_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  aux_engine_funcs ; 

struct aux_engine *dce110_aux_engine_construct(struct aux_engine_dce110 *aux_engine110,
		struct dc_context *ctx,
		uint32_t inst,
		uint32_t timeout_period,
		const struct dce110_aux_registers *regs)
{
	aux_engine110->base.ddc = NULL;
	aux_engine110->base.ctx = ctx;
	aux_engine110->base.delay = 0;
	aux_engine110->base.max_defer_write_retry = 0;
	aux_engine110->base.funcs = &aux_engine_funcs;
	aux_engine110->base.inst = inst;
	aux_engine110->timeout_period = timeout_period;
	aux_engine110->regs = regs;

	return &aux_engine110->base;
}