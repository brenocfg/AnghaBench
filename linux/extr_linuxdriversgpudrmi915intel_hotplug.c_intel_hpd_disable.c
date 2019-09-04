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
struct TYPE_4__ {TYPE_1__* stats; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; TYPE_2__ hotplug; } ;
typedef  enum hpd_pin { ____Placeholder_hpd_pin } hpd_pin ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ HPD_DISABLED ; 
 scalar_t__ HPD_ENABLED ; 
 int HPD_NONE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool intel_hpd_disable(struct drm_i915_private *dev_priv, enum hpd_pin pin)
{
	bool ret = false;

	if (pin == HPD_NONE)
		return false;

	spin_lock_irq(&dev_priv->irq_lock);
	if (dev_priv->hotplug.stats[pin].state == HPD_ENABLED) {
		dev_priv->hotplug.stats[pin].state = HPD_DISABLED;
		ret = true;
	}
	spin_unlock_irq(&dev_priv->irq_lock);

	return ret;
}