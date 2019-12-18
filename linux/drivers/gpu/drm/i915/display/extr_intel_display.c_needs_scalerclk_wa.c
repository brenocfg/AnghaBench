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
struct TYPE_2__ {scalar_t__ scaler_users; } ;
struct intel_crtc_state {TYPE_1__ scaler_state; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 

__attribute__((used)) static bool needs_scalerclk_wa(struct drm_i915_private *dev_priv,
			       const struct intel_crtc_state *crtc_state)
{
	/* Wa_2006604312:icl */
	if (crtc_state->scaler_state.scaler_users > 0 && IS_ICELAKE(dev_priv))
		return true;

	return false;
}