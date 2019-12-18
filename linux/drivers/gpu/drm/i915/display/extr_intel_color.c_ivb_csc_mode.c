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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ degamma_lut; } ;
struct intel_crtc_state {scalar_t__ output_format; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSC_POSITION_BEFORE_GAMMA ; 
 scalar_t__ INTEL_OUTPUT_FORMAT_RGB ; 
 int ilk_csc_limited_range (struct intel_crtc_state const*) ; 

__attribute__((used)) static u32 ivb_csc_mode(const struct intel_crtc_state *crtc_state)
{
	bool limited_color_range = ilk_csc_limited_range(crtc_state);

	/*
	 * CSC comes after the LUT in degamma, RGB->YCbCr,
	 * and RGB full->limited range mode.
	 */
	if (crtc_state->base.degamma_lut ||
	    crtc_state->output_format != INTEL_OUTPUT_FORMAT_RGB ||
	    limited_color_range)
		return 0;

	return CSC_POSITION_BEFORE_GAMMA;
}