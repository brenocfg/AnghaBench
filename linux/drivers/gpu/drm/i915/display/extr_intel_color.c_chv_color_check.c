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
struct intel_crtc_state {int gamma_enable; int /*<<< orphan*/  cgm_mode; int /*<<< orphan*/  gamma_mode; int /*<<< orphan*/  c8_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE_MODE_8BIT ; 
 int check_luts (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  chv_cgm_mode (struct intel_crtc_state*) ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct intel_crtc_state*) ; 
 int intel_color_add_affected_planes (struct intel_crtc_state*) ; 

__attribute__((used)) static int chv_color_check(struct intel_crtc_state *crtc_state)
{
	int ret;

	ret = check_luts(crtc_state);
	if (ret)
		return ret;

	/*
	 * Pipe gamma will be used only for the legacy LUT.
	 * Otherwise we bypass it and use the CGM gamma instead.
	 */
	crtc_state->gamma_enable =
		crtc_state_is_legacy_gamma(crtc_state) &&
		!crtc_state->c8_planes;

	crtc_state->gamma_mode = GAMMA_MODE_MODE_8BIT;

	crtc_state->cgm_mode = chv_cgm_mode(crtc_state);

	ret = intel_color_add_affected_planes(crtc_state);
	if (ret)
		return ret;

	return 0;
}