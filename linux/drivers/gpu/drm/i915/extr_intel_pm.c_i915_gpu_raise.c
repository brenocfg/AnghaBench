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
struct TYPE_2__ {scalar_t__ max_delay; scalar_t__ fmax; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; TYPE_1__ ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* mchdev_get () ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool i915_gpu_raise(void)
{
	struct drm_i915_private *i915;

	i915 = mchdev_get();
	if (!i915)
		return false;

	spin_lock_irq(&mchdev_lock);
	if (i915->ips.max_delay > i915->ips.fmax)
		i915->ips.max_delay--;
	spin_unlock_irq(&mchdev_lock);

	drm_dev_put(&i915->drm);
	return true;
}