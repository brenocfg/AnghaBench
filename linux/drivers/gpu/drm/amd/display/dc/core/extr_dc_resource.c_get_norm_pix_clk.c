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
typedef  int uint32_t ;
struct dc_crtc_timing {int pix_clk_100hz; scalar_t__ pixel_encoding; int display_color_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  COLOR_DEPTH_101010 132 
#define  COLOR_DEPTH_121212 131 
#define  COLOR_DEPTH_161616 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 

__attribute__((used)) static int get_norm_pix_clk(const struct dc_crtc_timing *timing)
{
	uint32_t pix_clk = timing->pix_clk_100hz;
	uint32_t normalized_pix_clk = pix_clk;

	if (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		pix_clk /= 2;
	if (timing->pixel_encoding != PIXEL_ENCODING_YCBCR422) {
		switch (timing->display_color_depth) {
		case COLOR_DEPTH_666:
		case COLOR_DEPTH_888:
			normalized_pix_clk = pix_clk;
			break;
		case COLOR_DEPTH_101010:
			normalized_pix_clk = (pix_clk * 30) / 24;
			break;
		case COLOR_DEPTH_121212:
			normalized_pix_clk = (pix_clk * 36) / 24;
		break;
		case COLOR_DEPTH_161616:
			normalized_pix_clk = (pix_clk * 48) / 24;
		break;
		default:
			ASSERT(0);
		break;
		}
	}
	return normalized_pix_clk;
}