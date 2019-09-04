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
struct TYPE_2__ {struct dc_context* ctx; int /*<<< orphan*/ * funcs; } ;
struct dce_mem_input {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_mem_input_v_funcs ; 

void dce110_mem_input_v_construct(
	struct dce_mem_input *dce_mi,
	struct dc_context *ctx)
{
	dce_mi->base.funcs = &dce110_mem_input_v_funcs;
	dce_mi->base.ctx = ctx;
}