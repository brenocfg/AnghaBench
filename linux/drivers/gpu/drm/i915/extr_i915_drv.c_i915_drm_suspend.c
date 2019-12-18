#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; int /*<<< orphan*/  suspend_count; TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_STATE_SUSPENDED ; 
 int /*<<< orphan*/  PCI_D1 ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_suspend_gtt_mappings (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_save_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_ucode_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_suspend (struct drm_device*) ; 
 int /*<<< orphan*/  intel_dp_mst_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbdev_set_suspend (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_hpd_cancel_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_suspend (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_power_domains_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_disable_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_suspend_encoders (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_suspend_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 scalar_t__ suspend_to_idle (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i915_drm_suspend(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;
	pci_power_t opregion_target_state;

	disable_rpm_wakeref_asserts(&dev_priv->runtime_pm);

	/* We do a lot of poking in a lot of registers, make sure they work
	 * properly. */
	intel_power_domains_disable(dev_priv);

	drm_kms_helper_poll_disable(dev);

	pci_save_state(pdev);

	intel_display_suspend(dev);

	intel_dp_mst_suspend(dev_priv);

	intel_runtime_pm_disable_interrupts(dev_priv);
	intel_hpd_cancel_work(dev_priv);

	intel_suspend_encoders(dev_priv);

	intel_suspend_hw(dev_priv);

	i915_gem_suspend_gtt_mappings(dev_priv);

	i915_save_state(dev_priv);

	opregion_target_state = suspend_to_idle(dev_priv) ? PCI_D1 : PCI_D3cold;
	intel_opregion_suspend(dev_priv, opregion_target_state);

	intel_fbdev_set_suspend(dev, FBINFO_STATE_SUSPENDED, true);

	dev_priv->suspend_count++;

	intel_csr_ucode_suspend(dev_priv);

	enable_rpm_wakeref_asserts(&dev_priv->runtime_pm);

	return 0;
}