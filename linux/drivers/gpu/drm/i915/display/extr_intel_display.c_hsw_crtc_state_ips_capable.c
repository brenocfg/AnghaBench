#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int pipe_bpp; int pixel_rate; TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct drm_i915_private {int max_cdclk_freq; } ;
struct TYPE_6__ {int /*<<< orphan*/  enable_ips; } ;

/* Variables and functions */
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_crtc_supports_ips (struct intel_crtc*) ; 
 TYPE_3__ i915_modparams ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

bool hsw_crtc_state_ips_capable(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	/* IPS only exists on ULT machines and is tied to pipe A. */
	if (!hsw_crtc_supports_ips(crtc))
		return false;

	if (!i915_modparams.enable_ips)
		return false;

	if (crtc_state->pipe_bpp > 24)
		return false;

	/*
	 * We compare against max which means we must take
	 * the increased cdclk requirement into account when
	 * calculating the new cdclk.
	 *
	 * Should measure whether using a lower cdclk w/o IPS
	 */
	if (IS_BROADWELL(dev_priv) &&
	    crtc_state->pixel_rate > dev_priv->max_cdclk_freq * 95 / 100)
		return false;

	return true;
}