#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int gsl_group; TYPE_5__* tg; } ;
struct pipe_ctx {TYPE_4__ stream_res; } ;
struct gsl_params {int gsl0_en; int gsl1_en; int gsl2_en; int gsl_master_en; } ;
struct dc {TYPE_2__* res_pool; } ;
struct TYPE_11__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_gsl_source_select ) (TYPE_5__*,int,int) ;int /*<<< orphan*/  (* set_gsl ) (TYPE_5__*,struct gsl_params*) ;} ;
struct TYPE_7__ {int gsl_0; int gsl_1; int gsl_2; } ;
struct TYPE_8__ {TYPE_1__ gsl_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int find_free_gsl_group (struct dc const*) ; 
 int /*<<< orphan*/  memset (struct gsl_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct gsl_params*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int,int) ; 

void dcn20_setup_gsl_group_as_lock(
		const struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		bool enable)
{
	struct gsl_params gsl;
	int group_idx;

	memset(&gsl, 0, sizeof(struct gsl_params));

	if (enable) {
		/* return if group already assigned since GSL was set up
		 * for vsync flip, we would unassign so it can't be "left over"
		 */
		if (pipe_ctx->stream_res.gsl_group > 0)
			return;

		group_idx = find_free_gsl_group(dc);
		ASSERT(group_idx != 0);
		pipe_ctx->stream_res.gsl_group = group_idx;

		/* set gsl group reg field and mark resource used */
		switch (group_idx) {
		case 1:
			gsl.gsl0_en = 1;
			dc->res_pool->gsl_groups.gsl_0 = 1;
			break;
		case 2:
			gsl.gsl1_en = 1;
			dc->res_pool->gsl_groups.gsl_1 = 1;
			break;
		case 3:
			gsl.gsl2_en = 1;
			dc->res_pool->gsl_groups.gsl_2 = 1;
			break;
		default:
			BREAK_TO_DEBUGGER();
			return; // invalid case
		}
		gsl.gsl_master_en = 1;
	} else {
		group_idx = pipe_ctx->stream_res.gsl_group;
		if (group_idx == 0)
			return; // if not in use, just return

		pipe_ctx->stream_res.gsl_group = 0;

		/* unset gsl group reg field and mark resource free */
		switch (group_idx) {
		case 1:
			gsl.gsl0_en = 0;
			dc->res_pool->gsl_groups.gsl_0 = 0;
			break;
		case 2:
			gsl.gsl1_en = 0;
			dc->res_pool->gsl_groups.gsl_1 = 0;
			break;
		case 3:
			gsl.gsl2_en = 0;
			dc->res_pool->gsl_groups.gsl_2 = 0;
			break;
		default:
			BREAK_TO_DEBUGGER();
			return;
		}
		gsl.gsl_master_en = 0;
	}

	/* at this point we want to program whether it's to enable or disable */
	if (pipe_ctx->stream_res.tg->funcs->set_gsl != NULL &&
		pipe_ctx->stream_res.tg->funcs->set_gsl_source_select != NULL) {
		pipe_ctx->stream_res.tg->funcs->set_gsl(
			pipe_ctx->stream_res.tg,
			&gsl);

		pipe_ctx->stream_res.tg->funcs->set_gsl_source_select(
			pipe_ctx->stream_res.tg, group_idx,	enable ? 4 : 0);
	} else
		BREAK_TO_DEBUGGER();
}