#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int h_total; int v_total; int v_addressable; int pix_clk_khz; } ;
struct dc_stream_state {TYPE_1__ timing; } ;
struct dc_state {size_t stream_count; struct dc_stream_state** streams; } ;

/* Variables and functions */

uint32_t dce110_get_min_vblank_time_us(const struct dc_state *context)
{
	uint8_t j;
	uint32_t min_vertical_blank_time = -1;

	for (j = 0; j < context->stream_count; j++) {
		struct dc_stream_state *stream = context->streams[j];
		uint32_t vertical_blank_in_pixels = 0;
		uint32_t vertical_blank_time = 0;

		vertical_blank_in_pixels = stream->timing.h_total *
			(stream->timing.v_total
			 - stream->timing.v_addressable);

		vertical_blank_time = vertical_blank_in_pixels
			* 1000 / stream->timing.pix_clk_khz;

		if (min_vertical_blank_time > vertical_blank_time)
			min_vertical_blank_time = vertical_blank_time;
	}

	return min_vertical_blank_time;
}