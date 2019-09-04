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
struct drm_i915_private {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  gamma_lut; int /*<<< orphan*/  degamma_lut; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {size_t degamma_lut_size; size_t gamma_lut_size; } ;
struct TYPE_4__ {TYPE_1__ color; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct drm_crtc_state*) ; 
 size_t drm_color_lut_size (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

int intel_color_check(struct drm_crtc *crtc,
		      struct drm_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	size_t gamma_length, degamma_length;

	degamma_length = INTEL_INFO(dev_priv)->color.degamma_lut_size;
	gamma_length = INTEL_INFO(dev_priv)->color.gamma_lut_size;

	/*
	 * We allow both degamma & gamma luts at the right size or
	 * NULL.
	 */
	if ((!crtc_state->degamma_lut ||
	     drm_color_lut_size(crtc_state->degamma_lut) == degamma_length) &&
	    (!crtc_state->gamma_lut ||
	     drm_color_lut_size(crtc_state->gamma_lut) == gamma_length))
		return 0;

	/*
	 * We also allow no degamma lut/ctm and a gamma lut at the legacy
	 * size (256 entries).
	 */
	if (crtc_state_is_legacy_gamma(crtc_state))
		return 0;

	return -EINVAL;
}