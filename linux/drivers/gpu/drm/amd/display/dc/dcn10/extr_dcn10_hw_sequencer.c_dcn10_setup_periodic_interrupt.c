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
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {TYPE_1__* funcs; } ;
struct TYPE_8__ {struct timing_generator* tg; } ;
struct pipe_ctx {TYPE_3__* stream; TYPE_4__ stream_res; } ;
typedef  enum vline_select { ____Placeholder_vline_select } vline_select ;
struct TYPE_6__ {int /*<<< orphan*/  lines_offset; } ;
struct TYPE_7__ {TYPE_2__ periodic_interrupt1; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* setup_vertical_interrupt1 ) (struct timing_generator*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setup_vertical_interrupt0 ) (struct timing_generator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int VLINE0 ; 
 int VLINE1 ; 
 int /*<<< orphan*/  cal_vline_position (struct pipe_ctx*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dcn10_setup_periodic_interrupt(
		struct pipe_ctx *pipe_ctx,
		enum vline_select vline)
{
	struct timing_generator *tg = pipe_ctx->stream_res.tg;

	if (vline == VLINE0) {
		uint32_t start_line = 0;
		uint32_t end_line = 0;

		cal_vline_position(pipe_ctx, vline, &start_line, &end_line);

		tg->funcs->setup_vertical_interrupt0(tg, start_line, end_line);

	} else if (vline == VLINE1) {
		pipe_ctx->stream_res.tg->funcs->setup_vertical_interrupt1(
				tg,
				pipe_ctx->stream->periodic_interrupt1.lines_offset);
	}
}