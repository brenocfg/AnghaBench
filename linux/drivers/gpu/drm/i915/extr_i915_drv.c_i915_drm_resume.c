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
struct TYPE_4__ {int /*<<< orphan*/  (* hpd_irq_setup ) (struct drm_i915_private*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; int /*<<< orphan*/  irq_lock; TYPE_2__ display; TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_gtt_mappings (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_sanitize (struct drm_i915_private*) ; 
 int i915_ggtt_enable_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_restore_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_ucode_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_resume (struct drm_device*) ; 
 int /*<<< orphan*/  intel_dp_mst_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbdev_set_suspend (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_clock_gating (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_pch_refclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_modeset_init_hw (struct drm_device*) ; 
 int /*<<< orphan*/  intel_opregion_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_pps_unlock_regs_wa (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_sanitize_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i915_drm_resume(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	int ret;

	disable_rpm_wakeref_asserts(&dev_priv->runtime_pm);
	intel_sanitize_gt_powersave(dev_priv);

	i915_gem_sanitize(dev_priv);

	ret = i915_ggtt_enable_hw(dev_priv);
	if (ret)
		DRM_ERROR("failed to re-enable GGTT\n");

	mutex_lock(&dev_priv->drm.struct_mutex);
	i915_gem_restore_gtt_mappings(dev_priv);
	i915_gem_restore_fences(dev_priv);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	intel_csr_ucode_resume(dev_priv);

	i915_restore_state(dev_priv);
	intel_pps_unlock_regs_wa(dev_priv);

	intel_init_pch_refclk(dev_priv);

	/*
	 * Interrupts have to be enabled before any batches are run. If not the
	 * GPU will hang. i915_gem_init_hw() will initiate batches to
	 * update/restore the context.
	 *
	 * drm_mode_config_reset() needs AUX interrupts.
	 *
	 * Modeset enabling in intel_modeset_init_hw() also needs working
	 * interrupts.
	 */
	intel_runtime_pm_enable_interrupts(dev_priv);

	drm_mode_config_reset(dev);

	i915_gem_resume(dev_priv);

	intel_modeset_init_hw(dev);
	intel_init_clock_gating(dev_priv);

	spin_lock_irq(&dev_priv->irq_lock);
	if (dev_priv->display.hpd_irq_setup)
		dev_priv->display.hpd_irq_setup(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	intel_dp_mst_resume(dev_priv);

	intel_display_resume(dev);

	drm_kms_helper_poll_enable(dev);

	/*
	 * ... but also need to make sure that hotplug processing
	 * doesn't cause havoc. Like in the driver load code we don't
	 * bother with the tiny race here where we might lose hotplug
	 * notifications.
	 * */
	intel_hpd_init(dev_priv);

	intel_opregion_resume(dev_priv);

	intel_fbdev_set_suspend(dev, FBINFO_STATE_RUNNING, false);

	intel_power_domains_enable(dev_priv);

	enable_rpm_wakeref_asserts(&dev_priv->runtime_pm);

	return 0;
}