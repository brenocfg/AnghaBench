#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  disable_power_well; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_RUNTIME_PM (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 TYPE_3__ i915_modparams ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_set_init_power (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

void intel_power_domains_fini(struct drm_i915_private *dev_priv)
{
	struct device *kdev = &dev_priv->drm.pdev->dev;

	/*
	 * The i915.ko module is still not prepared to be loaded when
	 * the power well is not enabled, so just enable it in case
	 * we're going to unload/reload.
	 * The following also reacquires the RPM reference the core passed
	 * to the driver during loading, which is dropped in
	 * intel_runtime_pm_enable(). We have to hand back the control of the
	 * device to the core with this reference held.
	 */
	intel_display_set_init_power(dev_priv, true);

	/* Remove the refcount we took to keep power well support disabled. */
	if (!i915_modparams.disable_power_well)
		intel_display_power_put(dev_priv, POWER_DOMAIN_INIT);

	/*
	 * Remove the refcount we took in intel_runtime_pm_enable() in case
	 * the platform doesn't support runtime PM.
	 */
	if (!HAS_RUNTIME_PM(dev_priv))
		pm_runtime_put(kdev);
}