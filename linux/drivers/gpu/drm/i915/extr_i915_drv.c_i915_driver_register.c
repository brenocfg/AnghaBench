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
struct drm_device {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ HAS_DISPLAY (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  VGT_DRV_DISPLAY_READY ; 
 int /*<<< orphan*/  acpi_video_register () ; 
 int /*<<< orphan*/  display_ready ; 
 scalar_t__ drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  i915_debugfs_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_driver_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_pmu_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_setup_sysfs (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_audio_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbdev_initial_config_async (struct drm_device*) ; 
 int /*<<< orphan*/  intel_gpu_ips_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vgtif_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_driver_register(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = &dev_priv->drm;

	i915_gem_driver_register(dev_priv);
	i915_pmu_register(dev_priv);

	/*
	 * Notify a valid surface after modesetting,
	 * when running inside a VM.
	 */
	if (intel_vgpu_active(dev_priv))
		I915_WRITE(vgtif_reg(display_ready), VGT_DRV_DISPLAY_READY);

	/* Reveal our presence to userspace */
	if (drm_dev_register(dev, 0) == 0) {
		i915_debugfs_register(dev_priv);
		i915_setup_sysfs(dev_priv);

		/* Depends on sysfs having been initialized */
		i915_perf_register(dev_priv);
	} else
		DRM_ERROR("Failed to register driver for userspace access!\n");

	if (HAS_DISPLAY(dev_priv)) {
		/* Must be done after probing outputs */
		intel_opregion_register(dev_priv);
		acpi_video_register();
	}

	if (IS_GEN(dev_priv, 5))
		intel_gpu_ips_init(dev_priv);

	intel_audio_init(dev_priv);

	/*
	 * Some ports require correctly set-up hpd registers for detection to
	 * work properly (leading to ghost connected connector status), e.g. VGA
	 * on gm45.  Hence we can only set up the initial fbdev config after hpd
	 * irqs are fully enabled. We do it last so that the async config
	 * cannot run before the connectors are registered.
	 */
	intel_fbdev_initial_config_async(dev);

	/*
	 * We need to coordinate the hotplugs with the asynchronous fbdev
	 * configuration, for which we use the fbdev->async_cookie.
	 */
	if (HAS_DISPLAY(dev_priv))
		drm_kms_helper_poll_init(dev);

	intel_power_domains_enable(dev_priv);
	intel_runtime_pm_enable(&dev_priv->runtime_pm);
}