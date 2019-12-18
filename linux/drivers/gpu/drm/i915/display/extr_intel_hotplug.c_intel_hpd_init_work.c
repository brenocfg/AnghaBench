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
struct TYPE_2__ {int /*<<< orphan*/  reenable_work; int /*<<< orphan*/  poll_init_work; int /*<<< orphan*/  dig_port_work; int /*<<< orphan*/  hotplug_work; } ;
struct drm_i915_private {TYPE_1__ hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_digport_work_func ; 
 int /*<<< orphan*/  i915_hotplug_work_func ; 
 int /*<<< orphan*/  i915_hpd_poll_init_work ; 
 int /*<<< orphan*/  intel_hpd_irq_storm_reenable_work ; 

void intel_hpd_init_work(struct drm_i915_private *dev_priv)
{
	INIT_DELAYED_WORK(&dev_priv->hotplug.hotplug_work,
			  i915_hotplug_work_func);
	INIT_WORK(&dev_priv->hotplug.dig_port_work, i915_digport_work_func);
	INIT_WORK(&dev_priv->hotplug.poll_init_work, i915_hpd_poll_init_work);
	INIT_DELAYED_WORK(&dev_priv->hotplug.reenable_work,
			  intel_hpd_irq_storm_reenable_work);
}