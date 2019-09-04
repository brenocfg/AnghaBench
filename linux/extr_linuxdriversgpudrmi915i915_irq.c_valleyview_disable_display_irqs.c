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
struct drm_i915_private {int display_irqs_enabled; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 scalar_t__ intel_irqs_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_display_irq_reset (struct drm_i915_private*) ; 

void valleyview_disable_display_irqs(struct drm_i915_private *dev_priv)
{
	lockdep_assert_held(&dev_priv->irq_lock);

	if (!dev_priv->display_irqs_enabled)
		return;

	dev_priv->display_irqs_enabled = false;

	if (intel_irqs_enabled(dev_priv))
		vlv_display_irq_reset(dev_priv);
}