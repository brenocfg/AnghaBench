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
struct i915_power_well {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  pcu_lock; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DP_SSC_MASK (int) ; 
 int DP_SSS_MASK (int) ; 
 int DP_SSS_PWR_GATE (int) ; 
 int DP_SSS_PWR_ON (int) ; 
 int PIPE_A ; 
 int /*<<< orphan*/  PUNIT_REG_DSPFREQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool chv_pipe_power_well_enabled(struct drm_i915_private *dev_priv,
					struct i915_power_well *power_well)
{
	enum pipe pipe = PIPE_A;
	bool enabled;
	u32 state, ctrl;

	mutex_lock(&dev_priv->pcu_lock);

	state = vlv_punit_read(dev_priv, PUNIT_REG_DSPFREQ) & DP_SSS_MASK(pipe);
	/*
	 * We only ever set the power-on and power-gate states, anything
	 * else is unexpected.
	 */
	WARN_ON(state != DP_SSS_PWR_ON(pipe) && state != DP_SSS_PWR_GATE(pipe));
	enabled = state == DP_SSS_PWR_ON(pipe);

	/*
	 * A transient state at this point would mean some unexpected party
	 * is poking at the power controls too.
	 */
	ctrl = vlv_punit_read(dev_priv, PUNIT_REG_DSPFREQ) & DP_SSC_MASK(pipe);
	WARN_ON(ctrl << 16 != state);

	mutex_unlock(&dev_priv->pcu_lock);

	return enabled;
}