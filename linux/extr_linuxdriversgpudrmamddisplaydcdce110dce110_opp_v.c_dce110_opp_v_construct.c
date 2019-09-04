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
struct dce110_opp {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  funcs ; 

void dce110_opp_v_construct(struct dce110_opp *opp110,
	struct dc_context *ctx)
{
	opp110->base.funcs = &funcs;

	opp110->base.ctx = ctx;
}