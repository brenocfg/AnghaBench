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
struct TYPE_3__ {int /*<<< orphan*/  hangcheck_work; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ gpu_error; TYPE_2__ drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  i915_driver_cleanup_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_cleanup_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_fini (struct drm_i915_private*) ; 
 scalar_t__ i915_gem_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_reset_error_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_bios_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_ucode_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_fbc_cleanup_cfb (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gvt_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_modeset_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  intel_power_domains_fini (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  vga_client_register (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (struct pci_dev*) ; 

void i915_driver_unload(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;

	i915_driver_unregister(dev_priv);

	if (i915_gem_suspend(dev_priv))
		DRM_ERROR("failed to idle hardware; continuing to unload!\n");

	intel_display_power_get(dev_priv, POWER_DOMAIN_INIT);

	drm_atomic_helper_shutdown(dev);

	intel_gvt_cleanup(dev_priv);

	intel_modeset_cleanup(dev);

	intel_bios_cleanup(dev_priv);

	vga_switcheroo_unregister_client(pdev);
	vga_client_register(pdev, NULL, NULL, NULL);

	intel_csr_ucode_fini(dev_priv);

	/* Free error state after interrupts are fully disabled. */
	cancel_delayed_work_sync(&dev_priv->gpu_error.hangcheck_work);
	i915_reset_error_state(dev_priv);

	i915_gem_fini(dev_priv);
	intel_fbc_cleanup_cfb(dev_priv);

	intel_power_domains_fini(dev_priv);

	i915_driver_cleanup_hw(dev_priv);
	i915_driver_cleanup_mmio(dev_priv);

	intel_display_power_put(dev_priv, POWER_DOMAIN_INIT);
}