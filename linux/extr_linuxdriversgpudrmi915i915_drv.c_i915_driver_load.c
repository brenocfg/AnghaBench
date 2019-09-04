#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct intel_device_info {int gen; } ;
struct TYPE_10__ {struct drm_i915_private* dev_private; struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_13__ {scalar_t__ num_pipes; } ;
struct TYPE_12__ {int /*<<< orphan*/  driver_features; } ;
struct TYPE_11__ {int /*<<< orphan*/  nuclear_pageflip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_FLAG_NEVER_SKIP ; 
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_9__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__ driver ; 
 int /*<<< orphan*/  drm_dev_fini (TYPE_1__*) ; 
 int drm_dev_init (TYPE_1__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int drm_vblank_init (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  i915_driver_cleanup_early (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_cleanup_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_cleanup_mmio (struct drm_i915_private*) ; 
 int i915_driver_init_early (struct drm_i915_private*,struct pci_device_id const*) ; 
 int i915_driver_init_hw (struct drm_i915_private*) ; 
 int i915_driver_init_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_register (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_load_error (struct drm_i915_private*,char*,int) ; 
 int i915_load_modeset_init (TYPE_1__*) ; 
 TYPE_2__ i915_modparams ; 
 int /*<<< orphan*/  i915_welcome_messages (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_ipc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kfree (struct drm_i915_private*) ; 
 struct drm_i915_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,TYPE_1__*) ; 

int i915_driver_load(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	const struct intel_device_info *match_info =
		(struct intel_device_info *)ent->driver_data;
	struct drm_i915_private *dev_priv;
	int ret;

	/* Enable nuclear pageflip on ILK+ */
	if (!i915_modparams.nuclear_pageflip && match_info->gen < 5)
		driver.driver_features &= ~DRIVER_ATOMIC;

	ret = -ENOMEM;
	dev_priv = kzalloc(sizeof(*dev_priv), GFP_KERNEL);
	if (dev_priv)
		ret = drm_dev_init(&dev_priv->drm, &driver, &pdev->dev);
	if (ret) {
		DRM_DEV_ERROR(&pdev->dev, "allocation failed\n");
		goto out_free;
	}

	dev_priv->drm.pdev = pdev;
	dev_priv->drm.dev_private = dev_priv;

	ret = pci_enable_device(pdev);
	if (ret)
		goto out_fini;

	pci_set_drvdata(pdev, &dev_priv->drm);
	/*
	 * Disable the system suspend direct complete optimization, which can
	 * leave the device suspended skipping the driver's suspend handlers
	 * if the device was already runtime suspended. This is needed due to
	 * the difference in our runtime and system suspend sequence and
	 * becaue the HDA driver may require us to enable the audio power
	 * domain during system suspend.
	 */
	dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_NEVER_SKIP);

	ret = i915_driver_init_early(dev_priv, ent);
	if (ret < 0)
		goto out_pci_disable;

	intel_runtime_pm_get(dev_priv);

	ret = i915_driver_init_mmio(dev_priv);
	if (ret < 0)
		goto out_runtime_pm_put;

	ret = i915_driver_init_hw(dev_priv);
	if (ret < 0)
		goto out_cleanup_mmio;

	/*
	 * TODO: move the vblank init and parts of modeset init steps into one
	 * of the i915_driver_init_/i915_driver_register functions according
	 * to the role/effect of the given init step.
	 */
	if (INTEL_INFO(dev_priv)->num_pipes) {
		ret = drm_vblank_init(&dev_priv->drm,
				      INTEL_INFO(dev_priv)->num_pipes);
		if (ret)
			goto out_cleanup_hw;
	}

	ret = i915_load_modeset_init(&dev_priv->drm);
	if (ret < 0)
		goto out_cleanup_hw;

	i915_driver_register(dev_priv);

	intel_runtime_pm_enable(dev_priv);

	intel_init_ipc(dev_priv);

	intel_runtime_pm_put(dev_priv);

	i915_welcome_messages(dev_priv);

	return 0;

out_cleanup_hw:
	i915_driver_cleanup_hw(dev_priv);
out_cleanup_mmio:
	i915_driver_cleanup_mmio(dev_priv);
out_runtime_pm_put:
	intel_runtime_pm_put(dev_priv);
	i915_driver_cleanup_early(dev_priv);
out_pci_disable:
	pci_disable_device(pdev);
out_fini:
	i915_load_error(dev_priv, "Device initialization failed (%d)\n", ret);
	drm_dev_fini(&dev_priv->drm);
out_free:
	kfree(dev_priv);
	pci_set_drvdata(pdev, NULL);
	return ret;
}