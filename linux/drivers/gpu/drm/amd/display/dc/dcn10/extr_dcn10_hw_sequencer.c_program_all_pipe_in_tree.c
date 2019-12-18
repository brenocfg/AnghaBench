#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* tg; } ;
struct TYPE_8__ {int /*<<< orphan*/  vupdate_width; int /*<<< orphan*/  vupdate_offset; int /*<<< orphan*/  vstartup_start; int /*<<< orphan*/  vready_offset; } ;
struct pipe_ctx {struct pipe_ctx* bottom_pipe; int /*<<< orphan*/ * plane_state; TYPE_4__* stream; TYPE_3__ stream_res; TYPE_1__ pipe_dlg_param; int /*<<< orphan*/ * top_pipe; } ;
struct dc_state {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* blank_pixel_data ) (struct dc*,struct pipe_ctx*,int) ;} ;
struct dc {TYPE_5__ hwss; } ;
struct TYPE_13__ {TYPE_2__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  timing; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_vtg_params ) (TYPE_6__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* program_global_sync ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_program_pipe (struct dc*,struct pipe_ctx*,struct dc_state*) ; 
 int /*<<< orphan*/  is_pipe_tree_visible (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct dc*,struct pipe_ctx*,int) ; 

__attribute__((used)) static void program_all_pipe_in_tree(
		struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context)
{
	if (pipe_ctx->top_pipe == NULL) {
		bool blank = !is_pipe_tree_visible(pipe_ctx);

		pipe_ctx->stream_res.tg->funcs->program_global_sync(
				pipe_ctx->stream_res.tg,
				pipe_ctx->pipe_dlg_param.vready_offset,
				pipe_ctx->pipe_dlg_param.vstartup_start,
				pipe_ctx->pipe_dlg_param.vupdate_offset,
				pipe_ctx->pipe_dlg_param.vupdate_width);

		pipe_ctx->stream_res.tg->funcs->set_vtg_params(
				pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing);

		dc->hwss.blank_pixel_data(dc, pipe_ctx, blank);

	}

	if (pipe_ctx->plane_state != NULL)
		dcn10_program_pipe(dc, pipe_ctx, context);

	if (pipe_ctx->bottom_pipe != NULL && pipe_ctx->bottom_pipe != pipe_ctx)
		program_all_pipe_in_tree(dc, pipe_ctx->bottom_pipe, context);
}