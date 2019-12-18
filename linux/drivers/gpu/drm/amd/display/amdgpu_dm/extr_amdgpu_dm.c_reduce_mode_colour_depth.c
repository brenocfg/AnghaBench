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
struct dc_crtc_timing {scalar_t__ display_color_depth; } ;

/* Variables and functions */
 scalar_t__ COLOR_DEPTH_888 ; 

__attribute__((used)) static void reduce_mode_colour_depth(struct dc_crtc_timing *timing_out)
{
	if (timing_out->display_color_depth <= COLOR_DEPTH_888)
		return;

	timing_out->display_color_depth--;
}