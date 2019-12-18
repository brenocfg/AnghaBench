#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {struct drm_property_blob* degamma_lut; struct drm_property_blob* gamma_lut; TYPE_1__* crtc; } ;
struct intel_crtc_state {scalar_t__ c8_planes; TYPE_2__ base; } ;
struct drm_property_blob {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_7__ {int degamma_lut_size; int gamma_lut_size; int /*<<< orphan*/  gamma_lut_tests; int /*<<< orphan*/  degamma_lut_tests; } ;
struct TYPE_8__ {TYPE_3__ color; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 TYPE_4__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ check_lut_size (struct drm_property_blob const*,int) ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct intel_crtc_state const*) ; 
 scalar_t__ drm_color_lut_check (struct drm_property_blob const*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_luts(const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);
	const struct drm_property_blob *gamma_lut = crtc_state->base.gamma_lut;
	const struct drm_property_blob *degamma_lut = crtc_state->base.degamma_lut;
	int gamma_length, degamma_length;
	u32 gamma_tests, degamma_tests;

	/* Always allow legacy gamma LUT with no further checking. */
	if (crtc_state_is_legacy_gamma(crtc_state))
		return 0;

	/* C8 relies on its palette being stored in the legacy LUT */
	if (crtc_state->c8_planes) {
		DRM_DEBUG_KMS("C8 pixelformat requires the legacy LUT\n");
		return -EINVAL;
	}

	degamma_length = INTEL_INFO(dev_priv)->color.degamma_lut_size;
	gamma_length = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	degamma_tests = INTEL_INFO(dev_priv)->color.degamma_lut_tests;
	gamma_tests = INTEL_INFO(dev_priv)->color.gamma_lut_tests;

	if (check_lut_size(degamma_lut, degamma_length) ||
	    check_lut_size(gamma_lut, gamma_length))
		return -EINVAL;

	if (drm_color_lut_check(degamma_lut, degamma_tests) ||
	    drm_color_lut_check(gamma_lut, gamma_tests))
		return -EINVAL;

	return 0;
}