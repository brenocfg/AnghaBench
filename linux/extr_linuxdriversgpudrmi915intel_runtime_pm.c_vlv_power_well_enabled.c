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
struct i915_power_well {int id; } ;
struct drm_i915_private {int /*<<< orphan*/  pcu_lock; } ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;

/* Variables and functions */
 int PUNIT_PWRGT_MASK (int) ; 
 int PUNIT_PWRGT_PWR_GATE (int) ; 
 int PUNIT_PWRGT_PWR_ON (int) ; 
 int /*<<< orphan*/  PUNIT_REG_PWRGT_CTRL ; 
 int /*<<< orphan*/  PUNIT_REG_PWRGT_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vlv_power_well_enabled(struct drm_i915_private *dev_priv,
				   struct i915_power_well *power_well)
{
	enum i915_power_well_id power_well_id = power_well->id;
	bool enabled = false;
	u32 mask;
	u32 state;
	u32 ctrl;

	mask = PUNIT_PWRGT_MASK(power_well_id);
	ctrl = PUNIT_PWRGT_PWR_ON(power_well_id);

	mutex_lock(&dev_priv->pcu_lock);

	state = vlv_punit_read(dev_priv, PUNIT_REG_PWRGT_STATUS) & mask;
	/*
	 * We only ever set the power-on and power-gate states, anything
	 * else is unexpected.
	 */
	WARN_ON(state != PUNIT_PWRGT_PWR_ON(power_well_id) &&
		state != PUNIT_PWRGT_PWR_GATE(power_well_id));
	if (state == ctrl)
		enabled = true;

	/*
	 * A transient state at this point would mean some unexpected party
	 * is poking at the power controls too.
	 */
	ctrl = vlv_punit_read(dev_priv, PUNIT_REG_PWRGT_CTRL) & mask;
	WARN_ON(ctrl != state);

	mutex_unlock(&dev_priv->pcu_lock);

	return enabled;
}