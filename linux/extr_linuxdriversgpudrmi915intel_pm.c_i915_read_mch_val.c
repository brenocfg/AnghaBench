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
 unsigned long __i915_chipset_val (struct drm_i915_private*) ; 
 unsigned long __i915_gfx_val (struct drm_i915_private*) ; 
 struct drm_i915_private* i915_mch_dev ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

unsigned long i915_read_mch_val(void)
{
	struct drm_i915_private *dev_priv;
	unsigned long chipset_val, graphics_val, ret = 0;

	spin_lock_irq(&mchdev_lock);
	if (!i915_mch_dev)
		goto out_unlock;
	dev_priv = i915_mch_dev;

	chipset_val = __i915_chipset_val(dev_priv);
	graphics_val = __i915_gfx_val(dev_priv);

	ret = chipset_val + graphics_val;

out_unlock:
	spin_unlock_irq(&mchdev_lock);

	return ret;
}