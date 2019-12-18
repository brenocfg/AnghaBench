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
struct timing_generator {TYPE_2__* funcs; } ;
struct TYPE_3__ {struct timing_generator* tg; } ;
struct pipe_ctx {TYPE_1__ stream_res; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* setup_vertical_interrupt2 ) (struct timing_generator*,int) ;} ;

/* Variables and functions */
 int get_vupdate_offset_from_vsync (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,int) ; 

void dcn20_setup_vupdate_interrupt(struct pipe_ctx *pipe_ctx)
{
	struct timing_generator *tg = pipe_ctx->stream_res.tg;
	int start_line = get_vupdate_offset_from_vsync(pipe_ctx);

	if (start_line < 0)
		start_line = 0;

	if (tg->funcs->setup_vertical_interrupt2)
		tg->funcs->setup_vertical_interrupt2(tg, start_line);
}