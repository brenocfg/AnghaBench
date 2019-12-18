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

/* Variables and functions */
 int /*<<< orphan*/  i915_hotplug_interrupt_update_locked (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_hotplug_interrupt_update(struct drm_i915_private *dev_priv,
				   u32 mask,
				   u32 bits)
{
	spin_lock_irq(&dev_priv->irq_lock);
	i915_hotplug_interrupt_update_locked(dev_priv, mask, bits);
	spin_unlock_irq(&dev_priv->irq_lock);
}