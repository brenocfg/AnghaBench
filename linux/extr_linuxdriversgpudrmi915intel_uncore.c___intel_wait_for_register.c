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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  FW_REG_READ ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int __intel_wait_for_register_fw (struct drm_i915_private*,int /*<<< orphan*/ ,int,int,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int __wait_for (int,int,unsigned int,int,int) ; 
 unsigned int intel_uncore_forcewake_for_reg (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  might_sleep_if (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int __intel_wait_for_register(struct drm_i915_private *dev_priv,
			    i915_reg_t reg,
			    u32 mask,
			    u32 value,
			    unsigned int fast_timeout_us,
			    unsigned int slow_timeout_ms,
			    u32 *out_value)
{
	unsigned fw =
		intel_uncore_forcewake_for_reg(dev_priv, reg, FW_REG_READ);
	u32 reg_value;
	int ret;

	might_sleep_if(slow_timeout_ms);

	spin_lock_irq(&dev_priv->uncore.lock);
	intel_uncore_forcewake_get__locked(dev_priv, fw);

	ret = __intel_wait_for_register_fw(dev_priv,
					   reg, mask, value,
					   fast_timeout_us, 0, &reg_value);

	intel_uncore_forcewake_put__locked(dev_priv, fw);
	spin_unlock_irq(&dev_priv->uncore.lock);

	if (ret && slow_timeout_ms)
		ret = __wait_for(reg_value = I915_READ_NOTRACE(reg),
				 (reg_value & mask) == value,
				 slow_timeout_ms * 1000, 10, 1000);

	if (out_value)
		*out_value = reg_value;

	return ret;
}