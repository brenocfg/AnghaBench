#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* pipe_ctx; } ;
struct dc_state {TYPE_2__ res_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* optimize_bandwidth ) (struct dc*,struct dc_state*) ;int /*<<< orphan*/  (* disable_plane ) (struct dc*,TYPE_4__*) ;} ;
struct dc {int optimized_required; TYPE_3__ hwss; TYPE_1__* res_pool; scalar_t__ optimize_seamless_boot; struct dc_state* current_state; } ;
struct TYPE_8__ {int pipe_idx; int /*<<< orphan*/ * plane_state; int /*<<< orphan*/ * stream; } ;
struct TYPE_5__ {int pipe_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  post_surface_trace (struct dc*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,struct dc_state*) ; 

bool dc_post_update_surfaces_to_stream(struct dc *dc)
{
	int i;
	struct dc_state *context = dc->current_state;

	if (!dc->optimized_required || dc->optimize_seamless_boot)
		return true;

	post_surface_trace(dc);

	for (i = 0; i < dc->res_pool->pipe_count; i++)
		if (context->res_ctx.pipe_ctx[i].stream == NULL ||
		    context->res_ctx.pipe_ctx[i].plane_state == NULL) {
			context->res_ctx.pipe_ctx[i].pipe_idx = i;
			dc->hwss.disable_plane(dc, &context->res_ctx.pipe_ctx[i]);
		}

	dc->optimized_required = false;

	dc->hwss.optimize_bandwidth(dc, context);
	return true;
}