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
typedef  unsigned long uint32_t ;
struct TYPE_2__ {unsigned long h_total; unsigned long pix_clk_khz; } ;
struct dc_stream_state {TYPE_1__ timing; } ;
struct bw_fixed {int value; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t compute_pstate_blackout_duration(
	struct bw_fixed blackout_duration,
	const struct dc_stream_state *stream)
{
	uint32_t total_dest_line_time_ns;
	uint32_t pstate_blackout_duration_ns;

	pstate_blackout_duration_ns = 1000 * blackout_duration.value >> 24;

	total_dest_line_time_ns = 1000000UL *
		stream->timing.h_total /
		stream->timing.pix_clk_khz +
		pstate_blackout_duration_ns;

	return total_dest_line_time_ns;
}