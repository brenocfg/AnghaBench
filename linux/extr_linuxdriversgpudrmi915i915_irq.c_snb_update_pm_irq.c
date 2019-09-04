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
typedef  int uint32_t ;
struct drm_i915_private {int pm_imr; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gen6_pm_imr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snb_update_pm_irq(struct drm_i915_private *dev_priv,
			      uint32_t interrupt_mask,
			      uint32_t enabled_irq_mask)
{
	uint32_t new_val;

	WARN_ON(enabled_irq_mask & ~interrupt_mask);

	lockdep_assert_held(&dev_priv->irq_lock);

	new_val = dev_priv->pm_imr;
	new_val &= ~interrupt_mask;
	new_val |= (~enabled_irq_mask & interrupt_mask);

	if (new_val != dev_priv->pm_imr) {
		dev_priv->pm_imr = new_val;
		I915_WRITE(gen6_pm_imr(dev_priv), dev_priv->pm_imr);
		POSTING_READ(gen6_pm_imr(dev_priv));
	}
}