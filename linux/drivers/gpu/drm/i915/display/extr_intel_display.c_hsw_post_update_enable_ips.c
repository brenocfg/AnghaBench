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
struct TYPE_4__ {int private_flags; } ;
struct TYPE_5__ {TYPE_1__ adjusted_mode; scalar_t__ color_mgmt_changed; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ gamma_mode; int /*<<< orphan*/  ips_enabled; TYPE_2__ base; scalar_t__ update_pipe; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_3__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ GAMMA_MODE_MODE_SPLIT ; 
 int I915_MODE_FLAG_INHERITED ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ needs_modeset (struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hsw_post_update_enable_ips(const struct intel_crtc_state *old_crtc_state,
				       const struct intel_crtc_state *new_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(new_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	if (!new_crtc_state->ips_enabled)
		return false;

	if (needs_modeset(new_crtc_state))
		return true;

	/*
	 * Workaround : Do not read or write the pipe palette/gamma data while
	 * GAMMA_MODE is configured for split gamma and IPS_CTL has IPS enabled.
	 *
	 * Re-enable IPS after the LUT has been programmed.
	 */
	if (IS_HASWELL(dev_priv) &&
	    (new_crtc_state->base.color_mgmt_changed ||
	     new_crtc_state->update_pipe) &&
	    new_crtc_state->gamma_mode == GAMMA_MODE_MODE_SPLIT)
		return true;

	/*
	 * We can't read out IPS on broadwell, assume the worst and
	 * forcibly enable IPS on the first fastset.
	 */
	if (new_crtc_state->update_pipe &&
	    old_crtc_state->base.adjusted_mode.private_flags & I915_MODE_FLAG_INHERITED)
		return true;

	return !old_crtc_state->ips_enabled;
}