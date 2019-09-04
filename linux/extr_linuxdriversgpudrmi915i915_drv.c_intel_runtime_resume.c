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
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int allowed_dc_mask; scalar_t__ dmc_payload; } ;
struct TYPE_3__ {int suspended; int /*<<< orphan*/  wakeref_count; } ;
struct drm_i915_private {TYPE_2__ csr; TYPE_1__ runtime_pm; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DC_STATE_EN_UPTO_DC5 ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_RUNTIME_PM (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxt_disable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_enable_dc5 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_disable_pc8 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_init_swizzling (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_enable_ipc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_notify_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_runtime_resume (struct drm_i915_private*) ; 
 scalar_t__ intel_uncore_unclaimed_mmio (struct drm_i915_private*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int vlv_resume_prepare (struct drm_i915_private*,int) ; 

__attribute__((used)) static int intel_runtime_resume(struct device *kdev)
{
	struct pci_dev *pdev = to_pci_dev(kdev);
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct drm_i915_private *dev_priv = to_i915(dev);
	int ret = 0;

	if (WARN_ON_ONCE(!HAS_RUNTIME_PM(dev_priv)))
		return -ENODEV;

	DRM_DEBUG_KMS("Resuming device\n");

	WARN_ON_ONCE(atomic_read(&dev_priv->runtime_pm.wakeref_count));
	disable_rpm_wakeref_asserts(dev_priv);

	intel_opregion_notify_adapter(dev_priv, PCI_D0);
	dev_priv->runtime_pm.suspended = false;
	if (intel_uncore_unclaimed_mmio(dev_priv))
		DRM_DEBUG_DRIVER("Unclaimed access during suspend, bios?\n");

	if (IS_GEN9_LP(dev_priv)) {
		bxt_disable_dc9(dev_priv);
		bxt_display_core_init(dev_priv, true);
		if (dev_priv->csr.dmc_payload &&
		    (dev_priv->csr.allowed_dc_mask & DC_STATE_EN_UPTO_DC5))
			gen9_enable_dc5(dev_priv);
	} else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		hsw_disable_pc8(dev_priv);
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		ret = vlv_resume_prepare(dev_priv, true);
	}

	intel_uncore_runtime_resume(dev_priv);

	intel_runtime_pm_enable_interrupts(dev_priv);

	intel_uc_resume(dev_priv);

	/*
	 * No point of rolling back things in case of an error, as the best
	 * we can do is to hope that things will still work (and disable RPM).
	 */
	i915_gem_init_swizzling(dev_priv);
	i915_gem_restore_fences(dev_priv);

	/*
	 * On VLV/CHV display interrupts are part of the display
	 * power well, so hpd is reinitialized from there. For
	 * everyone else do it here.
	 */
	if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		intel_hpd_init(dev_priv);

	intel_enable_ipc(dev_priv);

	enable_rpm_wakeref_asserts(dev_priv);

	if (ret)
		DRM_ERROR("Runtime resume failed, disabling it (%d)\n", ret);
	else
		DRM_DEBUG_KMS("Device resumed\n");

	return ret;
}