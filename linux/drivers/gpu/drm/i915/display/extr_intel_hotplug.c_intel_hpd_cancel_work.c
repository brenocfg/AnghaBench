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
struct TYPE_2__ {int /*<<< orphan*/  reenable_work; int /*<<< orphan*/  poll_init_work; int /*<<< orphan*/  hotplug_work; int /*<<< orphan*/  dig_port_work; scalar_t__ retry_bits; scalar_t__ event_bits; scalar_t__ short_port_mask; scalar_t__ long_port_mask; } ;
struct drm_i915_private {TYPE_1__ hotplug; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_hpd_cancel_work(struct drm_i915_private *dev_priv)
{
	spin_lock_irq(&dev_priv->irq_lock);

	dev_priv->hotplug.long_port_mask = 0;
	dev_priv->hotplug.short_port_mask = 0;
	dev_priv->hotplug.event_bits = 0;
	dev_priv->hotplug.retry_bits = 0;

	spin_unlock_irq(&dev_priv->irq_lock);

	cancel_work_sync(&dev_priv->hotplug.dig_port_work);
	cancel_delayed_work_sync(&dev_priv->hotplug.hotplug_work);
	cancel_work_sync(&dev_priv->hotplug.poll_init_work);
	cancel_delayed_work_sync(&dev_priv->hotplug.reenable_work);
}