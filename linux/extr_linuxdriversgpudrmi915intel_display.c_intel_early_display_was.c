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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHICKEN_PAR1_1 ; 
 int DARBF_GATING_DIS ; 
 int FORCE_ARB_IDLE_PLANES ; 
 int /*<<< orphan*/  GEN9_CLKGATE_DIS_0 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_early_display_was(struct drm_i915_private *dev_priv)
{
	/* Display WA #1185 WaDisableDARBFClkGating:cnl,glk */
	if (IS_CANNONLAKE(dev_priv) || IS_GEMINILAKE(dev_priv))
		I915_WRITE(GEN9_CLKGATE_DIS_0, I915_READ(GEN9_CLKGATE_DIS_0) |
			   DARBF_GATING_DIS);

	if (IS_HASWELL(dev_priv)) {
		/*
		 * WaRsPkgCStateDisplayPMReq:hsw
		 * System hang if this isn't done before disabling all planes!
		 */
		I915_WRITE(CHICKEN_PAR1_1,
			   I915_READ(CHICKEN_PAR1_1) | FORCE_ARB_IDLE_PLANES);
	}
}