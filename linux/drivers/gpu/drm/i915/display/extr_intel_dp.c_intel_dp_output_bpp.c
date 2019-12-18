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
struct intel_crtc_state {scalar_t__ output_format; } ;

/* Variables and functions */
 scalar_t__ INTEL_OUTPUT_FORMAT_YCBCR420 ; 

__attribute__((used)) static int intel_dp_output_bpp(const struct intel_crtc_state *crtc_state, int bpp)
{
	/*
	 * bpp value was assumed to RGB format. And YCbCr 4:2:0 output
	 * format of the number of bytes per pixel will be half the number
	 * of bytes of RGB pixel.
	 */
	if (crtc_state->output_format == INTEL_OUTPUT_FORMAT_YCBCR420)
		bpp /= 2;

	return bpp;
}