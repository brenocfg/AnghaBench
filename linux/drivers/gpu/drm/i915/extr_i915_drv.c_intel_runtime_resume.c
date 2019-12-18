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
struct intel_runtime_pm {int suspended; int /*<<< orphan*/  wakeref_count; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; int /*<<< orphan*/  uncore; struct intel_runtime_pm runtime_pm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_RUNTIME_PM (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_enable_ipc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_runtime_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_notify_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_runtime_resume (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_uncore_unclaimed_mmio (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 
 int vlv_resume_prepare (struct drm_i915_private*,int) ; 

__attribute__((used)) static int intel_runtime_resume(struct device *kdev)
{
	struct drm_i915_private *dev_priv = kdev_to_i915(kdev);
	struct intel_runtime_pm *rpm = &dev_priv->runtime_pm;
	int ret = 0;

	if (WARN_ON_ONCE(!HAS_RUNTIME_PM(dev_priv)))
		return -ENODEV;

	DRM_DEBUG_KMS("Resuming device\n");

	WARN_ON_ONCE(atomic_read(&rpm->wakeref_count));
	disable_rpm_wakeref_asserts(rpm);

	intel_opregion_notify_adapter(dev_priv, PCI_D0);
	rpm->suspended = false;
	if (intel_uncore_unclaimed_mmio(&dev_priv->uncore))
		DRM_DEBUG_DRIVER("Unclaimed access during suspend, bios?\n");

	intel_display_power_resume(dev_priv);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = vlv_resume_prepare(dev_priv, true);

	intel_uncore_runtime_resume(&dev_priv->uncore);

	intel_runtime_pm_enable_interrupts(dev_priv);

	/*
	 * No point of rolling back things in case of an error, as the best
	 * we can do is to hope that things will still work (and disable RPM).
	 */
	intel_gt_runtime_resume(&dev_priv->gt);
	i915_gem_restore_fences(dev_priv);

	/*
	 * On VLV/CHV display interrupts are part of the display
	 * power well, so hpd is reinitialized from there. For
	 * everyone else do it here.
	 */
	if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		intel_hpd_init(dev_priv);

	intel_enable_ipc(dev_priv);

	enable_rpm_wakeref_asserts(rpm);

	if (ret)
		DRM_ERROR("Runtime resume failed, disabling it (%d)\n", ret);
	else
		DRM_DEBUG_KMS("Device resumed\n");

	return ret;
}