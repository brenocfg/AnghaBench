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
struct drm_i915_private {int /*<<< orphan*/  drm; int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_video_unregister () ; 
 int /*<<< orphan*/  drm_dev_unplug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_driver_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_pmu_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_teardown_sysfs (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_audio_deinit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbdev_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gpu_ips_teardown () ; 
 int /*<<< orphan*/  intel_opregion_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_driver_unregister(struct drm_i915_private *dev_priv)
{
	intel_runtime_pm_disable(&dev_priv->runtime_pm);
	intel_power_domains_disable(dev_priv);

	intel_fbdev_unregister(dev_priv);
	intel_audio_deinit(dev_priv);

	/*
	 * After flushing the fbdev (incl. a late async config which will
	 * have delayed queuing of a hotplug event), then flush the hotplug
	 * events.
	 */
	drm_kms_helper_poll_fini(&dev_priv->drm);

	intel_gpu_ips_teardown();
	acpi_video_unregister();
	intel_opregion_unregister(dev_priv);

	i915_perf_unregister(dev_priv);
	i915_pmu_unregister(dev_priv);

	i915_teardown_sysfs(dev_priv);
	drm_dev_unplug(&dev_priv->drm);

	i915_gem_driver_unregister(dev_priv);
}