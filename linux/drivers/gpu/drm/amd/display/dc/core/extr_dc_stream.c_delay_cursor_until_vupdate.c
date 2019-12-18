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
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct TYPE_6__ {int h_total; int pix_clk_100hz; } ;
struct dc_stream_state {TYPE_3__ timing; TYPE_2__* ctx; } ;
struct dc {int dummy; } ;
struct TYPE_4__ {scalar_t__ chip_family; int /*<<< orphan*/  hw_internal_rev; } ;
struct TYPE_5__ {TYPE_1__ asic_id; } ;

/* Variables and functions */
 scalar_t__ ASICREV_IS_RAVEN (int /*<<< orphan*/ ) ; 
 scalar_t__ FAMILY_RV ; 
 int /*<<< orphan*/  dc_stream_get_crtc_position (struct dc*,struct dc_stream_state**,int,unsigned int*,unsigned int*) ; 
 unsigned int get_vupdate_offset_from_vsync (struct pipe_ctx*) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static void delay_cursor_until_vupdate(struct pipe_ctx *pipe_ctx, struct dc *dc)
{
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	unsigned int vupdate_line;
	unsigned int lines_to_vupdate, us_to_vupdate, vpos, nvpos;
	struct dc_stream_state *stream = pipe_ctx->stream;
	unsigned int us_per_line;

	if (stream->ctx->asic_id.chip_family == FAMILY_RV &&
			ASICREV_IS_RAVEN(stream->ctx->asic_id.hw_internal_rev)) {

		vupdate_line = get_vupdate_offset_from_vsync(pipe_ctx);
		if (!dc_stream_get_crtc_position(dc, &stream, 1, &vpos, &nvpos))
			return;

		if (vpos >= vupdate_line)
			return;

		us_per_line = stream->timing.h_total * 10000 / stream->timing.pix_clk_100hz;
		lines_to_vupdate = vupdate_line - vpos;
		us_to_vupdate = lines_to_vupdate * us_per_line;

		/* 70 us is a conservative estimate of cursor update time*/
		if (us_to_vupdate < 70)
			udelay(us_to_vupdate);
	}
#endif
}