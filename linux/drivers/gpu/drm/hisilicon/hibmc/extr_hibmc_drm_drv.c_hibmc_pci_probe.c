#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct drm_device {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hibmc_driver ; 
 int hibmc_load (struct drm_device*) ; 
 int /*<<< orphan*/  hibmc_unload (struct drm_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct drm_device*) ; 

__attribute__((used)) static int hibmc_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct drm_device *dev;
	int ret;

	dev = drm_dev_alloc(&hibmc_driver, &pdev->dev);
	if (IS_ERR(dev)) {
		DRM_ERROR("failed to allocate drm_device\n");
		return PTR_ERR(dev);
	}

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	ret = pci_enable_device(pdev);
	if (ret) {
		DRM_ERROR("failed to enable pci device: %d\n", ret);
		goto err_free;
	}

	ret = hibmc_load(dev);
	if (ret) {
		DRM_ERROR("failed to load hibmc: %d\n", ret);
		goto err_disable;
	}

	ret = drm_dev_register(dev, 0);
	if (ret) {
		DRM_ERROR("failed to register drv for userspace access: %d\n",
			  ret);
		goto err_unload;
	}
	return 0;

err_unload:
	hibmc_unload(dev);
err_disable:
	pci_disable_device(pdev);
err_free:
	drm_dev_put(dev);

	return ret;
}