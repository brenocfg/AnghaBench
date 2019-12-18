#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dc_stream_state {scalar_t__ signal; int /*<<< orphan*/  dpms_off; } ;
struct dc_state {int stream_count; struct dc_stream_state** streams; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_VIRTUAL ; 

int clk_mgr_helper_get_active_display_cnt(
		struct dc *dc,
		struct dc_state *context)
{
	int i, display_count;

	display_count = 0;
	for (i = 0; i < context->stream_count; i++) {
		const struct dc_stream_state *stream = context->streams[i];

		/*
		 * Only notify active stream or virtual stream.
		 * Need to notify virtual stream to work around
		 * headless case. HPD does not fire when system is in
		 * S0i2.
		 */
		if (!stream->dpms_off || stream->signal == SIGNAL_TYPE_VIRTUAL)
			display_count++;
	}

	return display_count;
}