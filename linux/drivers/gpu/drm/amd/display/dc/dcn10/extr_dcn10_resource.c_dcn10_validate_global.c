#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dc_state {int stream_count; TYPE_1__* stream_status; } ;
struct TYPE_9__ {int /*<<< orphan*/  enable; } ;
struct TYPE_8__ {int width; scalar_t__ height; } ;
struct TYPE_7__ {int width; scalar_t__ height; } ;
struct dc_plane_state {scalar_t__ format; TYPE_4__ dcc; TYPE_3__ src_rect; TYPE_2__ dst_rect; } ;
struct dc {TYPE_5__* dcn_soc; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_10__ {int number_of_channels; } ;
struct TYPE_6__ {int plane_count; struct dc_plane_state** plane_states; } ;

/* Variables and functions */
 int DC_FAIL_SURFACE_VALIDATE ; 
 int DC_FAIL_UNSUPPORTED_1 ; 
 int DC_OK ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 

__attribute__((used)) static enum dc_status dcn10_validate_global(struct dc *dc, struct dc_state *context)
{
	int i, j;
	bool video_down_scaled = false;
	bool video_large = false;
	bool desktop_large = false;
	bool dcc_disabled = false;

	for (i = 0; i < context->stream_count; i++) {
		if (context->stream_status[i].plane_count == 0)
			continue;

		if (context->stream_status[i].plane_count > 2)
			return DC_FAIL_UNSUPPORTED_1;

		for (j = 0; j < context->stream_status[i].plane_count; j++) {
			struct dc_plane_state *plane =
				context->stream_status[i].plane_states[j];


			if (plane->format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) {

				if (plane->src_rect.width > plane->dst_rect.width ||
						plane->src_rect.height > plane->dst_rect.height)
					video_down_scaled = true;

				if (plane->src_rect.width >= 3840)
					video_large = true;

			} else {
				if (plane->src_rect.width >= 3840)
					desktop_large = true;
				if (!plane->dcc.enable)
					dcc_disabled = true;
			}
		}
	}

	/*
	 * Workaround: On DCN10 there is UMC issue that causes underflow when
	 * playing 4k video on 4k desktop with video downscaled and single channel
	 * memory
	 */
	if (video_large && desktop_large && video_down_scaled && dcc_disabled &&
			dc->dcn_soc->number_of_channels == 1)
		return DC_FAIL_SURFACE_VALIDATE;

	return DC_OK;
}