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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct drm_i915_private {TYPE_1__ cdclk; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int D_COMP_COMP_DISABLE ; 
 int D_COMP_COMP_FORCE ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int LCPLL_CD_SOURCE_FCLK ; 
 int LCPLL_CD_SOURCE_FCLK_DONE ; 
 int /*<<< orphan*/  LCPLL_CTL ; 
 int LCPLL_PLL_DISABLE ; 
 int LCPLL_PLL_LOCK ; 
 int LCPLL_POWER_DOWN_ALLOW ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int hsw_read_dcomp (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_write_dcomp (struct drm_i915_private*,int) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  intel_dump_cdclk_state (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 scalar_t__ wait_for_us (int,int) ; 

__attribute__((used)) static void hsw_restore_lcpll(struct drm_i915_private *dev_priv)
{
	u32 val;

	val = I915_READ(LCPLL_CTL);

	if ((val & (LCPLL_PLL_LOCK | LCPLL_PLL_DISABLE | LCPLL_CD_SOURCE_FCLK |
		    LCPLL_POWER_DOWN_ALLOW)) == LCPLL_PLL_LOCK)
		return;

	/*
	 * Make sure we're not on PC8 state before disabling PC8, otherwise
	 * we'll hang the machine. To prevent PC8 state, just enable force_wake.
	 */
	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	if (val & LCPLL_POWER_DOWN_ALLOW) {
		val &= ~LCPLL_POWER_DOWN_ALLOW;
		I915_WRITE(LCPLL_CTL, val);
		POSTING_READ(LCPLL_CTL);
	}

	val = hsw_read_dcomp(dev_priv);
	val |= D_COMP_COMP_FORCE;
	val &= ~D_COMP_COMP_DISABLE;
	hsw_write_dcomp(dev_priv, val);

	val = I915_READ(LCPLL_CTL);
	val &= ~LCPLL_PLL_DISABLE;
	I915_WRITE(LCPLL_CTL, val);

	if (intel_de_wait_for_set(dev_priv, LCPLL_CTL, LCPLL_PLL_LOCK, 5))
		DRM_ERROR("LCPLL not locked yet\n");

	if (val & LCPLL_CD_SOURCE_FCLK) {
		val = I915_READ(LCPLL_CTL);
		val &= ~LCPLL_CD_SOURCE_FCLK;
		I915_WRITE(LCPLL_CTL, val);

		if (wait_for_us((I915_READ(LCPLL_CTL) &
				 LCPLL_CD_SOURCE_FCLK_DONE) == 0, 1))
			DRM_ERROR("Switching back to LCPLL failed\n");
	}

	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);

	intel_update_cdclk(dev_priv);
	intel_dump_cdclk_state(&dev_priv->cdclk.hw, "Current CDCLK");
}