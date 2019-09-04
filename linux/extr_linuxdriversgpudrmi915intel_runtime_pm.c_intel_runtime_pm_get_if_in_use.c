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
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  wakeref_count; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_2__ runtime_pm; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct drm_i915_private*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_get_if_in_use (struct device*) ; 

bool intel_runtime_pm_get_if_in_use(struct drm_i915_private *dev_priv)
{
	if (IS_ENABLED(CONFIG_PM)) {
		struct pci_dev *pdev = dev_priv->drm.pdev;
		struct device *kdev = &pdev->dev;

		/*
		 * In cases runtime PM is disabled by the RPM core and we get
		 * an -EINVAL return value we are not supposed to call this
		 * function, since the power state is undefined. This applies
		 * atm to the late/early system suspend/resume handlers.
		 */
		if (pm_runtime_get_if_in_use(kdev) <= 0)
			return false;
	}

	atomic_inc(&dev_priv->runtime_pm.wakeref_count);
	assert_rpm_wakelock_held(dev_priv);

	return true;
}