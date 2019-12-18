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
struct TYPE_6__ {int p2_fast; int p2_slow; int dot_limit; } ;
struct intel_limit {TYPE_3__ p2; } ;
struct TYPE_5__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_is_dual_link_lvds (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i9xx_select_p2_div(const struct intel_limit *limit,
		   const struct intel_crtc_state *crtc_state,
		   int target)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) {
		/*
		 * For LVDS just rely on its current settings for dual-channel.
		 * We haven't figured out how to reliably set up different
		 * single/dual channel state, if we even can.
		 */
		if (intel_is_dual_link_lvds(dev_priv))
			return limit->p2.p2_fast;
		else
			return limit->p2.p2_slow;
	} else {
		if (target < limit->p2.dot_limit)
			return limit->p2.p2_slow;
		else
			return limit->p2.p2_fast;
	}
}