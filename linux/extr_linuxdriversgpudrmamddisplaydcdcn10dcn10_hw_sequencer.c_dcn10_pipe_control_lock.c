#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* tg; } ;
struct pipe_ctx {TYPE_3__ stream_res; scalar_t__ top_pipe; } ;
struct TYPE_6__ {scalar_t__ sanity_checks; } ;
struct dc {TYPE_1__ debug; } ;
struct TYPE_9__ {TYPE_2__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* unlock ) (TYPE_4__*) ;int /*<<< orphan*/  (* lock ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_verify_allow_pstate_change_high (struct dc*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

__attribute__((used)) static void dcn10_pipe_control_lock(
	struct dc *dc,
	struct pipe_ctx *pipe,
	bool lock)
{
	/* use TG master update lock to lock everything on the TG
	 * therefore only top pipe need to lock
	 */
	if (pipe->top_pipe)
		return;

	if (dc->debug.sanity_checks)
		dcn10_verify_allow_pstate_change_high(dc);

	if (lock)
		pipe->stream_res.tg->funcs->lock(pipe->stream_res.tg);
	else
		pipe->stream_res.tg->funcs->unlock(pipe->stream_res.tg);

	if (dc->debug.sanity_checks)
		dcn10_verify_allow_pstate_change_high(dc);
}