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
struct drm_display_info {int max_tmds_clock; } ;
struct dc_crtc_timing {scalar_t__ display_color_depth; int pix_clk_100hz; scalar_t__ pixel_encoding; } ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 130 
#define  COLOR_DEPTH_121212 129 
#define  COLOR_DEPTH_161616 128 
 scalar_t__ COLOR_DEPTH_888 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 int /*<<< orphan*/  reduce_mode_colour_depth (struct dc_crtc_timing*) ; 

__attribute__((used)) static void adjust_colour_depth_from_display_info(struct dc_crtc_timing *timing_out,
						const struct drm_display_info *info)
{
	int normalized_clk;
	if (timing_out->display_color_depth <= COLOR_DEPTH_888)
		return;
	do {
		normalized_clk = timing_out->pix_clk_100hz / 10;
		/* YCbCr 4:2:0 requires additional adjustment of 1/2 */
		if (timing_out->pixel_encoding == PIXEL_ENCODING_YCBCR420)
			normalized_clk /= 2;
		/* Adjusting pix clock following on HDMI spec based on colour depth */
		switch (timing_out->display_color_depth) {
		case COLOR_DEPTH_101010:
			normalized_clk = (normalized_clk * 30) / 24;
			break;
		case COLOR_DEPTH_121212:
			normalized_clk = (normalized_clk * 36) / 24;
			break;
		case COLOR_DEPTH_161616:
			normalized_clk = (normalized_clk * 48) / 24;
			break;
		default:
			return;
		}
		if (normalized_clk <= info->max_tmds_clock)
			return;
		reduce_mode_colour_depth(timing_out);

	} while (timing_out->display_color_depth > COLOR_DEPTH_888);

}