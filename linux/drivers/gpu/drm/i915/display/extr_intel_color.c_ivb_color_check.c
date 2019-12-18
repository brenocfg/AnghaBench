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
struct TYPE_2__ {scalar_t__ ctm; scalar_t__ degamma_lut; scalar_t__ gamma_lut; } ;
struct intel_crtc_state {int gamma_enable; int csc_enable; scalar_t__ output_format; int /*<<< orphan*/  csc_mode; int /*<<< orphan*/  gamma_mode; TYPE_1__ base; int /*<<< orphan*/  c8_planes; } ;

/* Variables and functions */
 scalar_t__ INTEL_OUTPUT_FORMAT_RGB ; 
 int check_luts (struct intel_crtc_state*) ; 
 int ilk_csc_limited_range (struct intel_crtc_state*) ; 
 int intel_color_add_affected_planes (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  ivb_csc_mode (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  ivb_gamma_mode (struct intel_crtc_state*) ; 

__attribute__((used)) static int ivb_color_check(struct intel_crtc_state *crtc_state)
{
	bool limited_color_range = ilk_csc_limited_range(crtc_state);
	int ret;

	ret = check_luts(crtc_state);
	if (ret)
		return ret;

	crtc_state->gamma_enable =
		(crtc_state->base.gamma_lut ||
		 crtc_state->base.degamma_lut) &&
		!crtc_state->c8_planes;

	crtc_state->csc_enable =
		crtc_state->output_format != INTEL_OUTPUT_FORMAT_RGB ||
		crtc_state->base.ctm || limited_color_range;

	crtc_state->gamma_mode = ivb_gamma_mode(crtc_state);

	crtc_state->csc_mode = ivb_csc_mode(crtc_state);

	ret = intel_color_add_affected_planes(crtc_state);
	if (ret)
		return ret;

	return 0;
}