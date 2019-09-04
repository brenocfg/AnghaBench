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
typedef  int /*<<< orphan*/  u32 ;
struct i915_power_well {int dummy; } ;
struct i915_power_domains {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHICKEN_MISC_2 ; 
 int /*<<< orphan*/  CNL_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  DC_STATE_DISABLE ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_DISP_PW_1 ; 
 int /*<<< orphan*/  cnl_uninit_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_dbuf_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_power_well_disable (struct drm_i915_private*,struct i915_power_well*) ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void cnl_display_core_uninit(struct drm_i915_private *dev_priv)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	struct i915_power_well *well;
	u32 val;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* 1. Disable all display engine functions -> aready done */

	/* 2. Disable DBUF */
	gen9_dbuf_disable(dev_priv);

	/* 3. Disable CD clock */
	cnl_uninit_cdclk(dev_priv);

	/*
	 * 4. Disable Power Well 1 (PG1).
	 *    The AUX IO power wells are toggled on demand, so they are already
	 *    disabled at this point.
	 */
	mutex_lock(&power_domains->lock);
	well = lookup_power_well(dev_priv, SKL_DISP_PW_1);
	intel_power_well_disable(dev_priv, well);
	mutex_unlock(&power_domains->lock);

	usleep_range(10, 30);		/* 10 us delay per Bspec */

	/* 5. Disable Comp */
	val = I915_READ(CHICKEN_MISC_2);
	val |= CNL_COMP_PWR_DOWN;
	I915_WRITE(CHICKEN_MISC_2, val);
}