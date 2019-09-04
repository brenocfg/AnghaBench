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
struct TYPE_4__ {int /*<<< orphan*/ * dmc_payload; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int power_domains_suspended; TYPE_2__ csr; TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  bxt_enable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_enable_pc8 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend_late (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_set_init_power (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_power_domains_init_hw (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_power_domains_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_to_idle (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int vlv_suspend_complete (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_drm_suspend_late(struct drm_device *dev, bool hibernation)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int ret;

	disable_rpm_wakeref_asserts(dev_priv);

	i915_gem_suspend_late(dev_priv);

	intel_display_set_init_power(dev_priv, false);
	intel_uncore_suspend(dev_priv);

	/*
	 * In case of firmware assisted context save/restore don't manually
	 * deinit the power domains. This also means the CSR/DMC firmware will
	 * stay active, it will power down any HW resources as required and
	 * also enable deeper system power states that would be blocked if the
	 * firmware was inactive.
	 */
	if (IS_GEN9_LP(dev_priv) || hibernation || !suspend_to_idle(dev_priv) ||
	    dev_priv->csr.dmc_payload == NULL) {
		intel_power_domains_suspend(dev_priv);
		dev_priv->power_domains_suspended = true;
	}

	ret = 0;
	if (IS_GEN9_LP(dev_priv))
		bxt_enable_dc9(dev_priv);
	else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		hsw_enable_pc8(dev_priv);
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = vlv_suspend_complete(dev_priv);

	if (ret) {
		DRM_ERROR("Suspend complete failed: %d\n", ret);
		if (dev_priv->power_domains_suspended) {
			intel_power_domains_init_hw(dev_priv, true);
			dev_priv->power_domains_suspended = false;
		}

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
	enable_rpm_wakeref_asserts(dev_priv);

	return ret;
}