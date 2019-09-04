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
struct TYPE_2__ {scalar_t__ max_delay; scalar_t__ min_delay; } ;
struct drm_i915_private {TYPE_1__ ips; } ;

/* Variables and functions */
 struct drm_i915_private* i915_mch_dev ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool i915_gpu_lower(void)
{
	struct drm_i915_private *dev_priv;
	bool ret = true;

	spin_lock_irq(&mchdev_lock);
	if (!i915_mch_dev) {
		ret = false;
		goto out_unlock;
	}
	dev_priv = i915_mch_dev;

	if (dev_priv->ips.max_delay < dev_priv->ips.min_delay)
		dev_priv->ips.max_delay++;

out_unlock:
	spin_unlock_irq(&mchdev_lock);

	return ret;
}