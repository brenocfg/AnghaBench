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
struct TYPE_3__ {scalar_t__ compression_enable; } ;
struct intel_crtc_state {int has_psr2; TYPE_1__ dsc_params; } ;
struct TYPE_4__ {int debug; } ;
struct drm_i915_private {TYPE_2__ psr; } ;

/* Variables and functions */
#define  I915_PSR_DEBUG_DISABLE 129 
#define  I915_PSR_DEBUG_FORCE_PSR1 128 
 int I915_PSR_DEBUG_MODE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static bool intel_psr2_enabled(struct drm_i915_private *dev_priv,
			       const struct intel_crtc_state *crtc_state)
{
	/* Cannot enable DSC and PSR2 simultaneously */
	WARN_ON(crtc_state->dsc_params.compression_enable &&
		crtc_state->has_psr2);

	switch (dev_priv->psr.debug & I915_PSR_DEBUG_MODE_MASK) {
	case I915_PSR_DEBUG_DISABLE:
	case I915_PSR_DEBUG_FORCE_PSR1:
		return false;
	default:
		return crtc_state->has_psr2;
	}
}