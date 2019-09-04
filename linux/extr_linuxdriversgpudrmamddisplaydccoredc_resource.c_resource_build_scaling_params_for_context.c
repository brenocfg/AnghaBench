#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* pipe_ctx; } ;
struct dc_state {TYPE_1__ res_ctx; } ;
struct dc {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; int /*<<< orphan*/ * plane_state; } ;

/* Variables and functions */
 int DC_FAIL_SCALING ; 
 int DC_OK ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  resource_build_scaling_params (TYPE_2__*) ; 

enum dc_status resource_build_scaling_params_for_context(
	const struct dc  *dc,
	struct dc_state *context)
{
	int i;

	for (i = 0; i < MAX_PIPES; i++) {
		if (context->res_ctx.pipe_ctx[i].plane_state != NULL &&
				context->res_ctx.pipe_ctx[i].stream != NULL)
			if (!resource_build_scaling_params(&context->res_ctx.pipe_ctx[i]))
				return DC_FAIL_SCALING;
	}

	return DC_OK;
}