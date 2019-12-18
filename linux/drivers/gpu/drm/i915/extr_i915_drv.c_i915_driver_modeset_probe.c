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
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_pipes; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ HAS_DISPLAY (struct drm_i915_private*) ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 int drm_vblank_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_driver_release (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_driver_remove (struct drm_i915_private*) ; 
 int i915_gem_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_probe_failure (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_switcheroo_ops ; 
 int /*<<< orphan*/ * i915_vga_set_decode ; 
 int /*<<< orphan*/  intel_bios_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_ucode_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_ucode_init (struct drm_i915_private*) ; 
 int intel_fbdev_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_gmbus_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gmbus_teardown (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_ipc (struct drm_i915_private*) ; 
 int intel_irq_install (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_irq_uninstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_modeset_driver_remove (struct drm_device*) ; 
 int intel_modeset_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_overlay_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_driver_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_init_hw (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_register_dsm_handler () ; 
 int /*<<< orphan*/  intel_update_rawclk (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int vga_client_register (struct pci_dev*,struct drm_i915_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vga_switcheroo_register_client (struct pci_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (struct pci_dev*) ; 

__attribute__((used)) static int i915_driver_modeset_probe(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int ret;

	if (i915_inject_probe_failure(dev_priv))
		return -ENODEV;

	if (HAS_DISPLAY(dev_priv)) {
		ret = drm_vblank_init(&dev_priv->drm,
				      INTEL_INFO(dev_priv)->num_pipes);
		if (ret)
			goto out;
	}

	intel_bios_init(dev_priv);

	/* If we have > 1 VGA cards, then we need to arbitrate access
	 * to the common VGA resources.
	 *
	 * If we are a secondary display controller (!PCI_DISPLAY_CLASS_VGA),
	 * then we do not take part in VGA arbitration and the
	 * vga_client_register() fails with -ENODEV.
	 */
	ret = vga_client_register(pdev, dev_priv, NULL, i915_vga_set_decode);
	if (ret && ret != -ENODEV)
		goto out;

	intel_register_dsm_handler();

	ret = vga_switcheroo_register_client(pdev, &i915_switcheroo_ops, false);
	if (ret)
		goto cleanup_vga_client;

	/* must happen before intel_power_domains_init_hw() on VLV/CHV */
	intel_update_rawclk(dev_priv);

	intel_power_domains_init_hw(dev_priv, false);

	intel_csr_ucode_init(dev_priv);

	ret = intel_irq_install(dev_priv);
	if (ret)
		goto cleanup_csr;

	intel_gmbus_setup(dev_priv);

	/* Important: The output setup functions called by modeset_init need
	 * working irqs for e.g. gmbus and dp aux transfers. */
	ret = intel_modeset_init(dev);
	if (ret)
		goto cleanup_irq;

	ret = i915_gem_init(dev_priv);
	if (ret)
		goto cleanup_modeset;

	intel_overlay_setup(dev_priv);

	if (!HAS_DISPLAY(dev_priv))
		return 0;

	ret = intel_fbdev_init(dev);
	if (ret)
		goto cleanup_gem;

	/* Only enable hotplug handling once the fbdev is fully set up. */
	intel_hpd_init(dev_priv);

	intel_init_ipc(dev_priv);

	return 0;

cleanup_gem:
	i915_gem_suspend(dev_priv);
	i915_gem_driver_remove(dev_priv);
	i915_gem_driver_release(dev_priv);
cleanup_modeset:
	intel_modeset_driver_remove(dev);
cleanup_irq:
	intel_irq_uninstall(dev_priv);
	intel_gmbus_teardown(dev_priv);
cleanup_csr:
	intel_csr_ucode_fini(dev_priv);
	intel_power_domains_driver_remove(dev_priv);
	vga_switcheroo_unregister_client(pdev);
cleanup_vga_client:
	vga_client_register(pdev, NULL, NULL, NULL);
out:
	return ret;
}