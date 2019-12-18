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
typedef  int u32 ;
struct i915_power_well {TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int idx; } ;
struct TYPE_4__ {TYPE_1__ vlv; } ;

/* Variables and functions */
 int PUNIT_PWRGT_MASK (int) ; 
 int PUNIT_PWRGT_PWR_GATE (int) ; 
 int PUNIT_PWRGT_PWR_ON (int) ; 
 int /*<<< orphan*/  PUNIT_REG_PWRGT_CTRL ; 
 int /*<<< orphan*/  PUNIT_REG_PWRGT_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  vlv_punit_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_put (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vlv_power_well_enabled(struct drm_i915_private *dev_priv,
				   struct i915_power_well *power_well)
{
	int pw_idx = power_well->desc->vlv.idx;
	bool enabled = false;
	u32 mask;
	u32 state;
	u32 ctrl;

	mask = PUNIT_PWRGT_MASK(pw_idx);
	ctrl = PUNIT_PWRGT_PWR_ON(pw_idx);

	vlv_punit_get(dev_priv);

	state = vlv_punit_read(dev_priv, PUNIT_REG_PWRGT_STATUS) & mask;
	/*
	 * We only ever set the power-on and power-gate states, anything
	 * else is unexpected.
	 */
	WARN_ON(state != PUNIT_PWRGT_PWR_ON(pw_idx) &&
		state != PUNIT_PWRGT_PWR_GATE(pw_idx));
	if (state == ctrl)
		enabled = true;

	/*
	 * A transient state at this point would mean some unexpected party
	 * is poking at the power controls too.
	 */
	ctrl = vlv_punit_read(dev_priv, PUNIT_REG_PWRGT_CTRL) & mask;
	WARN_ON(ctrl != state);

	vlv_punit_put(dev_priv);

	return enabled;
}