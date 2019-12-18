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
struct intel_runtime_pm {int suspended; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;
struct TYPE_4__ {TYPE_1__ rc6; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; int /*<<< orphan*/  gt; TYPE_2__ gt_pm; struct intel_runtime_pm runtime_pm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENODEV ; 
 scalar_t__ HAS_RC6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_RUNTIME_PM (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D1 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  assert_forcewakes_inactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_runtime_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_runtime_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_runtime_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hpd_poll_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_notify_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_disable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_driver_release (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable_interrupts (struct drm_i915_private*) ; 
 scalar_t__ intel_uncore_arm_unclaimed_mmio_detection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_runtime_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_suspend (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 
 int vlv_suspend_complete (struct drm_i915_private*) ; 

__attribute__((used)) static int intel_runtime_suspend(struct device *kdev)
{
	struct drm_i915_private *dev_priv = kdev_to_i915(kdev);
	struct intel_runtime_pm *rpm = &dev_priv->runtime_pm;
	int ret = 0;

	if (WARN_ON_ONCE(!(dev_priv->gt_pm.rc6.enabled && HAS_RC6(dev_priv))))
		return -ENODEV;

	if (WARN_ON_ONCE(!HAS_RUNTIME_PM(dev_priv)))
		return -ENODEV;

	DRM_DEBUG_KMS("Suspending device\n");

	disable_rpm_wakeref_asserts(rpm);

	/*
	 * We are safe here against re-faults, since the fault handler takes
	 * an RPM reference.
	 */
	i915_gem_runtime_suspend(dev_priv);

	intel_gt_runtime_suspend(&dev_priv->gt);

	intel_runtime_pm_disable_interrupts(dev_priv);

	intel_uncore_suspend(&dev_priv->uncore);

	intel_display_power_suspend(dev_priv);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = vlv_suspend_complete(dev_priv);

	if (ret) {
		DRM_ERROR("Runtime suspend failed, disabling it (%d)\n", ret);
		intel_uncore_runtime_resume(&dev_priv->uncore);

		intel_runtime_pm_enable_interrupts(dev_priv);

		intel_gt_runtime_resume(&dev_priv->gt);

		i915_gem_restore_fences(dev_priv);

		enable_rpm_wakeref_asserts(rpm);

		return ret;
	}

	enable_rpm_wakeref_asserts(rpm);
	intel_runtime_pm_driver_release(rpm);

	if (intel_uncore_arm_unclaimed_mmio_detection(&dev_priv->uncore))
		DRM_ERROR("Unclaimed access detected prior to suspending\n");

	rpm->suspended = true;

	/*
	 * FIXME: We really should find a document that references the arguments
	 * used below!
	 */
	if (IS_BROADWELL(dev_priv)) {
		/*
		 * On Broadwell, if we use PCI_D1 the PCH DDI ports will stop
		 * being detected, and the call we do at intel_runtime_resume()
		 * won't be able to restore them. Since PCI_D3hot matches the
		 * actual specification and appears to be working, use it.
		 */
		intel_opregion_notify_adapter(dev_priv, PCI_D3hot);
	} else {
		/*
		 * current versions of firmware which depend on this opregion
		 * notification have repurposed the D1 definition to mean
		 * "runtime suspended" vs. what you would normally expect (D3)
		 * to distinguish it from notifications that might be sent via
		 * the suspend path.
		 */
		intel_opregion_notify_adapter(dev_priv, PCI_D1);
	}

	assert_forcewakes_inactive(&dev_priv->uncore);

	if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		intel_hpd_poll_init(dev_priv);

	DRM_DEBUG_KMS("Device suspended\n");
	return 0;
}