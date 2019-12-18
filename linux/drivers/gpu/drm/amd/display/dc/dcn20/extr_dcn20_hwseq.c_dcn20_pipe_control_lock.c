#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ gsl_group; TYPE_4__* tg; } ;
struct pipe_ctx {TYPE_3__ stream_res; TYPE_1__* plane_state; int /*<<< orphan*/ * bottom_pipe; scalar_t__ top_pipe; } ;
struct dc {int dummy; } ;
struct TYPE_11__ {TYPE_2__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* unlock ) (TYPE_4__*) ;int /*<<< orphan*/  (* lock ) (TYPE_4__*) ;int /*<<< orphan*/  (* triplebuffer_unlock ) (TYPE_4__*) ;int /*<<< orphan*/  (* triplebuffer_lock ) (TYPE_4__*) ;} ;
struct TYPE_8__ {int flip_immediate; scalar_t__ triplebuffer_flips; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn20_setup_gsl_group_as_lock (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

void dcn20_pipe_control_lock(
	struct dc *dc,
	struct pipe_ctx *pipe,
	bool lock)
{
	bool flip_immediate = false;

	/* use TG master update lock to lock everything on the TG
	 * therefore only top pipe need to lock
	 */
	if (pipe->top_pipe)
		return;

	if (pipe->plane_state != NULL)
		flip_immediate = pipe->plane_state->flip_immediate;

	/* In flip immediate and pipe splitting case, we need to use GSL
	 * for synchronization. Only do setup on locking and on flip type change.
	 */
	if (lock && pipe->bottom_pipe != NULL)
		if ((flip_immediate && pipe->stream_res.gsl_group == 0) ||
		    (!flip_immediate && pipe->stream_res.gsl_group > 0))
			dcn20_setup_gsl_group_as_lock(dc, pipe, flip_immediate);

	if (pipe->plane_state != NULL && pipe->plane_state->triplebuffer_flips) {
		if (lock)
			pipe->stream_res.tg->funcs->triplebuffer_lock(pipe->stream_res.tg);
		else
			pipe->stream_res.tg->funcs->triplebuffer_unlock(pipe->stream_res.tg);
	} else {
		if (lock)
			pipe->stream_res.tg->funcs->lock(pipe->stream_res.tg);
		else
			pipe->stream_res.tg->funcs->unlock(pipe->stream_res.tg);
	}
}