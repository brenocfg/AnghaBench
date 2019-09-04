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
struct intel_crtc_state {scalar_t__ gamma_mode; scalar_t__ ips_enabled; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {struct drm_crtc* crtc; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GAMMA_MODE_MODE_8BIT ; 
 scalar_t__ GAMMA_MODE_MODE_SPLIT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_disable_ips (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  hsw_enable_ips (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_load_luts (struct drm_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void haswell_load_luts(struct drm_crtc_state *crtc_state)
{
	struct drm_crtc *crtc = crtc_state->crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_crtc_state *intel_crtc_state =
		to_intel_crtc_state(crtc_state);
	bool reenable_ips = false;

	/*
	 * Workaround : Do not read or write the pipe palette/gamma data while
	 * GAMMA_MODE is configured for split gamma and IPS_CTL has IPS enabled.
	 */
	if (IS_HASWELL(dev_priv) && intel_crtc_state->ips_enabled &&
	    (intel_crtc_state->gamma_mode == GAMMA_MODE_MODE_SPLIT)) {
		hsw_disable_ips(intel_crtc_state);
		reenable_ips = true;
	}

	intel_crtc_state->gamma_mode = GAMMA_MODE_MODE_8BIT;
	I915_WRITE(GAMMA_MODE(intel_crtc->pipe), GAMMA_MODE_MODE_8BIT);

	i9xx_load_luts(crtc_state);

	if (reenable_ips)
		hsw_enable_ips(intel_crtc_state);
}