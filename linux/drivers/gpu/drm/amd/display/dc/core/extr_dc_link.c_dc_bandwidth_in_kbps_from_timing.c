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
struct TYPE_4__ {int Y_ONLY; scalar_t__ DSC; } ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct dc_crtc_timing {int pix_clk_100hz; int display_color_depth; scalar_t__ pixel_encoding; TYPE_2__ flags; TYPE_1__ dsc_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  COLOR_DEPTH_101010 133 
#define  COLOR_DEPTH_121212 132 
#define  COLOR_DEPTH_141414 131 
#define  COLOR_DEPTH_161616 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 

uint32_t dc_bandwidth_in_kbps_from_timing(
	const struct dc_crtc_timing *timing)
{
	uint32_t bits_per_channel = 0;
	uint32_t kbps;

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	if (timing->flags.DSC) {
		kbps = (timing->pix_clk_100hz * timing->dsc_cfg.bits_per_pixel);
		kbps = kbps / 160 + ((kbps % 160) ? 1 : 0);
		return kbps;
	}
#endif

	switch (timing->display_color_depth) {
	case COLOR_DEPTH_666:
		bits_per_channel = 6;
		break;
	case COLOR_DEPTH_888:
		bits_per_channel = 8;
		break;
	case COLOR_DEPTH_101010:
		bits_per_channel = 10;
		break;
	case COLOR_DEPTH_121212:
		bits_per_channel = 12;
		break;
	case COLOR_DEPTH_141414:
		bits_per_channel = 14;
		break;
	case COLOR_DEPTH_161616:
		bits_per_channel = 16;
		break;
	default:
		break;
	}

	ASSERT(bits_per_channel != 0);

	kbps = timing->pix_clk_100hz / 10;
	kbps *= bits_per_channel;

	if (timing->flags.Y_ONLY != 1) {
		/*Only YOnly make reduce bandwidth by 1/3 compares to RGB*/
		kbps *= 3;
		if (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
			kbps /= 2;
		else if (timing->pixel_encoding == PIXEL_ENCODING_YCBCR422)
			kbps = kbps * 2 / 3;
	}

	return kbps;

}