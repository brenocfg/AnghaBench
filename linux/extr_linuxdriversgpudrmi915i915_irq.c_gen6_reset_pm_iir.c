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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_pm_iir (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen6_reset_pm_iir(struct drm_i915_private *dev_priv, u32 reset_mask)
{
	i915_reg_t reg = gen6_pm_iir(dev_priv);

	lockdep_assert_held(&dev_priv->irq_lock);

	I915_WRITE(reg, reset_mask);
	I915_WRITE(reg, reset_mask);
	POSTING_READ(reg);
}