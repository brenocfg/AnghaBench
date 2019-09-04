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
struct drm_i915_private {int /*<<< orphan*/  pm_ier; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_pm_ier (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_unmask_pm_irq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen6_enable_pm_irq(struct drm_i915_private *dev_priv, u32 enable_mask)
{
	lockdep_assert_held(&dev_priv->irq_lock);

	dev_priv->pm_ier |= enable_mask;
	I915_WRITE(gen6_pm_ier(dev_priv), dev_priv->pm_ier);
	gen6_unmask_pm_irq(dev_priv, enable_mask);
	/* unmask_pm_irq provides an implicit barrier (POSTING_READ) */
}