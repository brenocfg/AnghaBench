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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHICKEN_MISC_2 ; 
 int /*<<< orphan*/  GEN9_CLKGATE_DIS_0 ; 
 int GLK_CL0_PWR_DOWN ; 
 int GLK_CL1_PWR_DOWN ; 
 int GLK_CL2_PWR_DOWN ; 
 int /*<<< orphan*/  GLK_REVID_A1 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GLK_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PWM1_GATING_DIS ; 
 int PWM2_GATING_DIS ; 
 int /*<<< orphan*/  gen9_init_clock_gating (struct drm_i915_private*) ; 

__attribute__((used)) static void glk_init_clock_gating(struct drm_i915_private *dev_priv)
{
	gen9_init_clock_gating(dev_priv);

	/*
	 * WaDisablePWMClockGating:glk
	 * Backlight PWM may stop in the asserted state, causing backlight
	 * to stay fully on.
	 */
	I915_WRITE(GEN9_CLKGATE_DIS_0, I915_READ(GEN9_CLKGATE_DIS_0) |
		   PWM1_GATING_DIS | PWM2_GATING_DIS);

	/* WaDDIIOTimeout:glk */
	if (IS_GLK_REVID(dev_priv, 0, GLK_REVID_A1)) {
		u32 val = I915_READ(CHICKEN_MISC_2);
		val &= ~(GLK_CL0_PWR_DOWN |
			 GLK_CL1_PWR_DOWN |
			 GLK_CL2_PWR_DOWN);
		I915_WRITE(CHICKEN_MISC_2, val);
	}

}