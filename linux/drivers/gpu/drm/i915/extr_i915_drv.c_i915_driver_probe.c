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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int dummy; } ;
struct intel_device_info {int gen; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver_features; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; TYPE_2__ drm; } ;
struct TYPE_3__ {int /*<<< orphan*/  nuclear_pageflip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 scalar_t__ IS_ERR (struct drm_i915_private*) ; 
 int PTR_ERR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_detect_vgpu (struct drm_i915_private*) ; 
 struct drm_i915_private* i915_driver_create (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  i915_driver_destroy (struct drm_i915_private*) ; 
 int i915_driver_early_probe (struct drm_i915_private*) ; 
 int i915_driver_hw_probe (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_hw_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_late_release (struct drm_i915_private*) ; 
 int i915_driver_mmio_probe (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_mmio_release (struct drm_i915_private*) ; 
 int i915_driver_modeset_probe (TYPE_2__*) ; 
 int /*<<< orphan*/  i915_driver_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_ggtt_driver_release (struct drm_i915_private*) ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  i915_probe_error (struct drm_i915_private*,char*,int) ; 
 int /*<<< orphan*/  i915_welcome_messages (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_sanitize_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 

int i915_driver_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	const struct intel_device_info *match_info =
		(struct intel_device_info *)ent->driver_data;
	struct drm_i915_private *dev_priv;
	int ret;

	dev_priv = i915_driver_create(pdev, ent);
	if (IS_ERR(dev_priv))
		return PTR_ERR(dev_priv);

	/* Disable nuclear pageflip by default on pre-ILK */
	if (!i915_modparams.nuclear_pageflip && match_info->gen < 5)
		dev_priv->drm.driver_features &= ~DRIVER_ATOMIC;

	ret = pci_enable_device(pdev);
	if (ret)
		goto out_fini;

	ret = i915_driver_early_probe(dev_priv);
	if (ret < 0)
		goto out_pci_disable;

	disable_rpm_wakeref_asserts(&dev_priv->runtime_pm);

	i915_detect_vgpu(dev_priv);

	ret = i915_driver_mmio_probe(dev_priv);
	if (ret < 0)
		goto out_runtime_pm_put;

	ret = i915_driver_hw_probe(dev_priv);
	if (ret < 0)
		goto out_cleanup_mmio;

	ret = i915_driver_modeset_probe(&dev_priv->drm);
	if (ret < 0)
		goto out_cleanup_hw;

	i915_driver_register(dev_priv);

	enable_rpm_wakeref_asserts(&dev_priv->runtime_pm);

	i915_welcome_messages(dev_priv);

	return 0;

out_cleanup_hw:
	i915_driver_hw_remove(dev_priv);
	i915_ggtt_driver_release(dev_priv);

	/* Paranoia: make sure we have disabled everything before we exit. */
	intel_sanitize_gt_powersave(dev_priv);
out_cleanup_mmio:
	i915_driver_mmio_release(dev_priv);
out_runtime_pm_put:
	enable_rpm_wakeref_asserts(&dev_priv->runtime_pm);
	i915_driver_late_release(dev_priv);
out_pci_disable:
	pci_disable_device(pdev);
out_fini:
	i915_probe_error(dev_priv, "Device initialization failed (%d)\n", ret);
	i915_driver_destroy(dev_priv);
	return ret;
}