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
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct drm_i915_private*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 

void intel_runtime_pm_get_noresume(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct device *kdev = &pdev->dev;

	assert_rpm_wakelock_held(dev_priv);
	pm_runtime_get_noresume(kdev);

	atomic_inc(&dev_priv->runtime_pm.wakeref_count);
}