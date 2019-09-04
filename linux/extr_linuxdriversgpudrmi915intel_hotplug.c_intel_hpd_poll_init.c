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
struct TYPE_2__ {int /*<<< orphan*/  poll_init_work; int /*<<< orphan*/  poll_enabled; } ;
struct drm_i915_private {TYPE_1__ hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void intel_hpd_poll_init(struct drm_i915_private *dev_priv)
{
	WRITE_ONCE(dev_priv->hotplug.poll_enabled, true);

	/*
	 * We might already be holding dev->mode_config.mutex, so do this in a
	 * seperate worker
	 * As well, there's no issue if we race here since we always reschedule
	 * this worker anyway
	 */
	schedule_work(&dev_priv->hotplug.poll_init_work);
}