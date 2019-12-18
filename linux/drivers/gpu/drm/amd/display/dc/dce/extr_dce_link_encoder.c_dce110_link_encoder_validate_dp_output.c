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
struct dce110_link_encoder {int dummy; } ;
struct dc_crtc_timing {scalar_t__ pixel_encoding; } ;

/* Variables and functions */
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 

bool dce110_link_encoder_validate_dp_output(
	const struct dce110_link_encoder *enc110,
	const struct dc_crtc_timing *crtc_timing)
{
	if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		return false;

	return true;
}