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
struct intel_runtime_pm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_forcewake_count; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_2__ uncore; struct intel_runtime_pm runtime_pm; TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  get_suspend_mode (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  i915_gem_suspend_late (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_rc6_ctx_wa_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_suspend_late (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_suspend (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_driver_release (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_uncore_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int vlv_suspend_complete (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_drm_suspend_late(struct drm_device *dev, bool hibernation)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct intel_runtime_pm *rpm = &dev_priv->runtime_pm;
	int ret = 0;

	disable_rpm_wakeref_asserts(rpm);

	i915_gem_suspend_late(dev_priv);

	i915_rc6_ctx_wa_suspend(dev_priv);

	intel_uncore_suspend(&dev_priv->uncore);

	intel_power_domains_suspend(dev_priv,
				    get_suspend_mode(dev_priv, hibernation));

	intel_display_power_suspend_late(dev_priv);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = vlv_suspend_complete(dev_priv);

	if (ret) {
		DRM_ERROR("Suspend complete failed: %d\n", ret);
		intel_power_domains_resume(dev_priv);

		goto out;
	}

	pci_disable_device(pdev);
	/*
	 * During hibernation on some platforms the BIOS may try to access
	 * the device even though it's already in D3 and hang the machine. So
	 * leave the device in D0 on those platforms and hope the BIOS will
	 * power down the device properly. The issue was seen on multiple old
	 * GENs with different BIOS vendors, so having an explicit blacklist
	 * is inpractical; apply the workaround on everything pre GEN6. The
	 * platforms where the issue was seen:
	 * Lenovo Thinkpad X301, X61s, X60, T60, X41
	 * Fujitsu FSC S7110
	 * Acer Aspire 1830T
	 */
	if (!(hibernation && INTEL_GEN(dev_priv) < 6))
		pci_set_power_state(pdev, PCI_D3hot);

out:
	enable_rpm_wakeref_asserts(rpm);
	if (!dev_priv->uncore.user_forcewake_count)
		intel_runtime_pm_driver_release(rpm);

	return ret;
}