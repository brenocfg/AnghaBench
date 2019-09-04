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
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_RUNTIME_PM (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

void intel_runtime_pm_enable(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct device *kdev = &pdev->dev;

	pm_runtime_set_autosuspend_delay(kdev, 10000); /* 10s */
	pm_runtime_mark_last_busy(kdev);

	/*
	 * Take a permanent reference to disable the RPM functionality and drop
	 * it only when unloading the driver. Use the low level get/put helpers,
	 * so the driver's own RPM reference tracking asserts also work on
	 * platforms without RPM support.
	 */
	if (!HAS_RUNTIME_PM(dev_priv)) {
		int ret;

		pm_runtime_dont_use_autosuspend(kdev);
		ret = pm_runtime_get_sync(kdev);
		WARN(ret < 0, "pm_runtime_get_sync() failed: %d\n", ret);
	} else {
		pm_runtime_use_autosuspend(kdev);
	}

	/*
	 * The core calls the driver load handler with an RPM reference held.
	 * We drop that here and will reacquire it during unloading in
	 * intel_power_domains_fini().
	 */
	pm_runtime_put_autosuspend(kdev);
}