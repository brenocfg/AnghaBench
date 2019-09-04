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
 int /*<<< orphan*/  IS_GEN5 (struct drm_i915_private*) ; 
 unsigned long __i915_gfx_val (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

unsigned long i915_gfx_val(struct drm_i915_private *dev_priv)
{
	unsigned long val;

	if (!IS_GEN5(dev_priv))
		return 0;

	spin_lock_irq(&mchdev_lock);

	val = __i915_gfx_val(dev_priv);

	spin_unlock_irq(&mchdev_lock);

	return val;
}