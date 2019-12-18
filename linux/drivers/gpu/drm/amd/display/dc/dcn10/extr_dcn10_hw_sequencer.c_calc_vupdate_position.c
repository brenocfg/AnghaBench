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
typedef  int uint32_t ;
struct pipe_ctx {TYPE_2__* stream; } ;
struct dc_crtc_timing {int v_total; } ;
struct TYPE_3__ {int lines_offset; } ;
struct TYPE_4__ {TYPE_1__ periodic_interrupt0; struct dc_crtc_timing timing; } ;

/* Variables and functions */
 int get_vupdate_offset_from_vsync (struct pipe_ctx*) ; 

__attribute__((used)) static void calc_vupdate_position(
		struct pipe_ctx *pipe_ctx,
		uint32_t *start_line,
		uint32_t *end_line)
{
	const struct dc_crtc_timing *dc_crtc_timing = &pipe_ctx->stream->timing;
	int vline_int_offset_from_vupdate =
			pipe_ctx->stream->periodic_interrupt0.lines_offset;
	int vupdate_offset_from_vsync = get_vupdate_offset_from_vsync(pipe_ctx);
	int start_position;

	if (vline_int_offset_from_vupdate > 0)
		vline_int_offset_from_vupdate--;
	else if (vline_int_offset_from_vupdate < 0)
		vline_int_offset_from_vupdate++;

	start_position = vline_int_offset_from_vupdate + vupdate_offset_from_vsync;

	if (start_position >= 0)
		*start_line = start_position;
	else
		*start_line = dc_crtc_timing->v_total + start_position - 1;

	*end_line = *start_line + 2;

	if (*end_line >= dc_crtc_timing->v_total)
		*end_line = 2;
}