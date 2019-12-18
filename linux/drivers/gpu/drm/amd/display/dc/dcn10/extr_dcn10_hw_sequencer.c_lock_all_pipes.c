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
struct timing_generator {TYPE_4__* funcs; } ;
struct TYPE_7__ {struct timing_generator* tg; } ;
struct pipe_ctx {int /*<<< orphan*/  plane_state; int /*<<< orphan*/  stream; scalar_t__ top_pipe; TYPE_3__ stream_res; } ;
struct TYPE_6__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_2__ res_ctx; } ;
struct dc {TYPE_1__* res_pool; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* unlock ) (struct timing_generator*) ;int /*<<< orphan*/  (* lock ) (struct timing_generator*) ;int /*<<< orphan*/  (* is_tg_enabled ) (struct timing_generator*) ;} ;
struct TYPE_5__ {int pipe_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub3 (struct timing_generator*) ; 

void lock_all_pipes(struct dc *dc,
	struct dc_state *context,
	bool lock)
{
	struct pipe_ctx *pipe_ctx;
	struct timing_generator *tg;
	int i;

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		pipe_ctx = &context->res_ctx.pipe_ctx[i];
		tg = pipe_ctx->stream_res.tg;
		/*
		 * Only lock the top pipe's tg to prevent redundant
		 * (un)locking. Also skip if pipe is disabled.
		 */
		if (pipe_ctx->top_pipe ||
		    !pipe_ctx->stream || !pipe_ctx->plane_state ||
		    !tg->funcs->is_tg_enabled(tg))
			continue;

		if (lock)
			tg->funcs->lock(tg);
		else
			tg->funcs->unlock(tg);
	}
}