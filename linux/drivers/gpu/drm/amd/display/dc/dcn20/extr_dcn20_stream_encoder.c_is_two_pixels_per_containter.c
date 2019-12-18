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
struct TYPE_4__ {int /*<<< orphan*/  ycbcr422_simple; } ;
struct TYPE_3__ {scalar_t__ DSC; } ;
struct dc_crtc_timing {scalar_t__ pixel_encoding; TYPE_2__ dsc_cfg; TYPE_1__ flags; } ;

/* Variables and functions */
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 

__attribute__((used)) static bool is_two_pixels_per_containter(const struct dc_crtc_timing *timing)
{
	bool two_pix = timing->pixel_encoding == PIXEL_ENCODING_YCBCR420;

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	two_pix = two_pix || (timing->flags.DSC && timing->pixel_encoding == PIXEL_ENCODING_YCBCR422
			&& !timing->dsc_cfg.ycbcr422_simple);
#endif
	return two_pix;
}