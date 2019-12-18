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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ ctm; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ output_format; int /*<<< orphan*/  csc_mode; scalar_t__ csc_enable; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INTEL_OUTPUT_FORMAT_RGB ; 
 int /*<<< orphan*/  IS_CANNONLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_CSC_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * ilk_csc_coeff_identity ; 
 int /*<<< orphan*/ * ilk_csc_coeff_limited_range ; 
 int /*<<< orphan*/ * ilk_csc_coeff_rgb_to_ycbcr ; 
 int /*<<< orphan*/  ilk_csc_convert_ctm (struct intel_crtc_state const*,int /*<<< orphan*/ *) ; 
 int ilk_csc_limited_range (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  ilk_csc_off_zero ; 
 int /*<<< orphan*/  ilk_csc_postoff_limited_range ; 
 int /*<<< orphan*/  ilk_csc_postoff_rgb_to_ycbcr ; 
 int /*<<< orphan*/  ilk_update_pipe_csc (struct intel_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_load_csc_matrix(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	bool limited_color_range = ilk_csc_limited_range(crtc_state);

	if (crtc_state->base.ctm) {
		u16 coeff[9];

		ilk_csc_convert_ctm(crtc_state, coeff);
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero, coeff,
				    limited_color_range ?
				    ilk_csc_postoff_limited_range :
				    ilk_csc_off_zero);
	} else if (crtc_state->output_format != INTEL_OUTPUT_FORMAT_RGB) {
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    ilk_csc_coeff_rgb_to_ycbcr,
				    ilk_csc_postoff_rgb_to_ycbcr);
	} else if (limited_color_range) {
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    ilk_csc_coeff_limited_range,
				    ilk_csc_postoff_limited_range);
	} else if (crtc_state->csc_enable) {
		/*
		 * On GLK+ both pipe CSC and degamma LUT are controlled
		 * by csc_enable. Hence for the cases where the degama
		 * LUT is needed but CSC is not we need to load an
		 * identity matrix.
		 */
		WARN_ON(!IS_CANNONLAKE(dev_priv) && !IS_GEMINILAKE(dev_priv));

		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    ilk_csc_coeff_identity,
				    ilk_csc_off_zero);
	}

	I915_WRITE(PIPE_CSC_MODE(crtc->pipe), crtc_state->csc_mode);
}