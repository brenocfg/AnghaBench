#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vstartup_start; } ;
struct pipe_ctx {TYPE_2__ pipe_dlg_param; TYPE_3__* stream; } ;
struct TYPE_4__ {scalar_t__ INTERLACE; } ;
struct dc_crtc_timing {int v_addressable; int v_border_bottom; int v_front_porch; int v_total; int v_border_top; TYPE_1__ flags; } ;
struct TYPE_6__ {struct dc_crtc_timing timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_front_porch_workaround (struct dc_crtc_timing*) ; 

int get_vupdate_offset_from_vsync(struct pipe_ctx *pipe_ctx)
{
	const struct dc_crtc_timing *dc_crtc_timing = &pipe_ctx->stream->timing;
	struct dc_crtc_timing patched_crtc_timing;
	int vesa_sync_start;
	int asic_blank_end;
	int interlace_factor;
	int vertical_line_start;

	patched_crtc_timing = *dc_crtc_timing;
	apply_front_porch_workaround(&patched_crtc_timing);

	interlace_factor = patched_crtc_timing.flags.INTERLACE ? 2 : 1;

	vesa_sync_start = patched_crtc_timing.v_addressable +
			patched_crtc_timing.v_border_bottom +
			patched_crtc_timing.v_front_porch;

	asic_blank_end = (patched_crtc_timing.v_total -
			vesa_sync_start -
			patched_crtc_timing.v_border_top)
			* interlace_factor;

	vertical_line_start = asic_blank_end -
			pipe_ctx->pipe_dlg_param.vstartup_start + 1;

	return vertical_line_start;
}