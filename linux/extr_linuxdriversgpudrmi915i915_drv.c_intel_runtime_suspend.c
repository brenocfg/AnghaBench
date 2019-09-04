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
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int suspended; int /*<<< orphan*/  wakeref_count; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_5__ {TYPE_1__ rc6; } ;
struct drm_i915_private {TYPE_3__ runtime_pm; TYPE_2__ gt_pm; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENODEV ; 
 scalar_t__ HAS_RC6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_RUNTIME_PM (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D1 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  assert_forcewakes_inactive (struct drm_i915_private*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxt_display_core_uninit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_enable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_enable_pc8 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_init_swizzling (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_runtime_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_poll_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_notify_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_disable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_suspend (struct drm_i915_private*) ; 
 scalar_t__ intel_uncore_arm_unclaimed_mmio_detection (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_runtime_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_suspend (struct drm_i915_private*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int vlv_suspend_complete (struct drm_i915_private*) ; 

__attribute__((used)) static int intel_runtime_suspend(struct device *kdev)
{
	struct pci_dev *pdev = to_pci_dev(kdev);
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct drm_i915_private *dev_priv = to_i915(dev);
	int ret;

	if (WARN_ON_ONCE(!(dev_priv->gt_pm.rc6.enabled && HAS_RC6(dev_priv))))
		return -ENODEV;

	if (WARN_ON_ONCE(!HAS_RUNTIME_PM(dev_priv)))
		return -ENODEV;

	DRM_DEBUG_KMS("Suspending device\n");

	disable_rpm_wakeref_asserts(dev_priv);

	/*
	 * We are safe here against re-faults, since the fault handler takes
	 * an RPM reference.
	 */
	i915_gem_runtime_suspend(dev_priv);

	intel_uc_suspend(dev_priv);

	intel_runtime_pm_disable_interrupts(dev_priv);

	intel_uncore_suspend(dev_priv);

	ret = 0;
	if (IS_GEN9_LP(dev_priv)) {
		bxt_display_core_uninit(dev_priv);
		bxt_enable_dc9(dev_priv);
	} else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		hsw_enable_pc8(dev_priv);
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		ret = vlv_suspend_complete(dev_priv);
	}

	if (ret) {
		DRM_ERROR("Runtime suspend failed, disabling it (%d)\n", ret);
		intel_uncore_runtime_resume(dev_priv);

		intel_runtime_pm_enable_interrupts(dev_priv);

		intel_uc_resume(dev_priv);

		i915_gem_init_swizzling(dev_priv);
		i915_gem_restore_fences(dev_priv);

		enable_rpm_wakeref_asserts(dev_priv);

		return ret;
	}

	enable_rpm_wakeref_asserts(dev_priv);
	WARN_ON_ONCE(atomic_read(&dev_priv->runtime_pm.wakeref_count));

	if (intel_uncore_arm_unclaimed_mmio_detection(dev_priv))
		DRM_ERROR("Unclaimed access detected prior to suspending\n");

	dev_priv->runtime_pm.suspended = true;

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

	assert_forcewakes_inactive(dev_priv);

	if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		intel_hpd_poll_init(dev_priv);

	DRM_DEBUG_KMS("Device suspended\n");
	return 0;
}