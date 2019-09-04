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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 struct drm_i915_private* i915_mch_dev ; 
 int /*<<< orphan*/  ips_ping_for_i915_load () ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_gpu_ips_init(struct drm_i915_private *dev_priv)
{
	/* We only register the i915 ips part with intel-ips once everything is
	 * set up, to avoid intel-ips sneaking in and reading bogus values. */
	spin_lock_irq(&mchdev_lock);
	i915_mch_dev = dev_priv;
	spin_unlock_irq(&mchdev_lock);

	ips_ping_for_i915_load();
}