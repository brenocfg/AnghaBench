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
 int BXT_DSIA_16X_MASK ; 
 int BXT_DSIC_16X_MASK ; 
 int /*<<< orphan*/  BXT_DSI_PLL_CTL ; 
 int BXT_DSI_PLL_DO_ENABLE ; 
 int /*<<< orphan*/  BXT_DSI_PLL_ENABLE ; 
 int BXT_DSI_PLL_LOCKED ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 

bool bxt_dsi_pll_is_enabled(struct drm_i915_private *dev_priv)
{
	bool enabled;
	u32 val;
	u32 mask;

	mask = BXT_DSI_PLL_DO_ENABLE | BXT_DSI_PLL_LOCKED;
	val = I915_READ(BXT_DSI_PLL_ENABLE);
	enabled = (val & mask) == mask;

	if (!enabled)
		return false;

	/*
	 * Dividers must be programmed with valid values. As per BSEPC, for
	 * GEMINLAKE only PORT A divider values are checked while for BXT
	 * both divider values are validated. Check this here for
	 * paranoia, since BIOS is known to misconfigure PLLs in this way at
	 * times, and since accessing DSI registers with invalid dividers
	 * causes a system hang.
	 */
	val = I915_READ(BXT_DSI_PLL_CTL);
	if (IS_GEMINILAKE(dev_priv)) {
		if (!(val & BXT_DSIA_16X_MASK)) {
			DRM_DEBUG_DRIVER("Invalid PLL divider (%08x)\n", val);
			enabled = false;
		}
	} else {
		if (!(val & BXT_DSIA_16X_MASK) || !(val & BXT_DSIC_16X_MASK)) {
			DRM_DEBUG_DRIVER("Invalid PLL divider (%08x)\n", val);
			enabled = false;
		}
	}

	return enabled;
}