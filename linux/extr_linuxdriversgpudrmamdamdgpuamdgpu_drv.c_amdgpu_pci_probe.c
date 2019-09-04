#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {unsigned long driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct drm_device {struct pci_dev* pdev; } ;
struct TYPE_3__ {int driver_features; } ;

/* Variables and functions */
 unsigned long AMD_ASIC_MASK ; 
 unsigned long AMD_EXP_HW_SUPPORT ; 
 int DRIVER_ATOMIC ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int EAGAIN ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int amdgpu_amdkfd_init () ; 
 scalar_t__ amdgpu_device_asic_has_dc_support (unsigned long) ; 
 int /*<<< orphan*/  amdgpu_exp_hw_support ; 
 int amdgpu_kick_out_firmware_fb (struct pci_dev*) ; 
 int /*<<< orphan*/  amdgpu_virtual_display ; 
 struct drm_device* drm_dev_alloc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,unsigned long) ; 
 TYPE_1__ kms_driver ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct drm_device*) ; 

__attribute__((used)) static int amdgpu_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	struct drm_device *dev;
	unsigned long flags = ent->driver_data;
	int ret, retry = 0;
	bool supports_atomic = false;

	if (!amdgpu_virtual_display &&
	    amdgpu_device_asic_has_dc_support(flags & AMD_ASIC_MASK))
		supports_atomic = true;

	if ((flags & AMD_EXP_HW_SUPPORT) && !amdgpu_exp_hw_support) {
		DRM_INFO("This hardware requires experimental hardware support.\n"
			 "See modparam exp_hw_support\n");
		return -ENODEV;
	}

	/*
	 * Initialize amdkfd before starting radeon. If it was not loaded yet,
	 * defer radeon probing
	 */
	ret = amdgpu_amdkfd_init();
	if (ret == -EPROBE_DEFER)
		return ret;

	/* Get rid of things like offb */
	ret = amdgpu_kick_out_firmware_fb(pdev);
	if (ret)
		return ret;

	/* warn the user if they mix atomic and non-atomic capable GPUs */
	if ((kms_driver.driver_features & DRIVER_ATOMIC) && !supports_atomic)
		DRM_ERROR("Mixing atomic and non-atomic capable GPUs!\n");
	/* support atomic early so the atomic debugfs stuff gets created */
	if (supports_atomic)
		kms_driver.driver_features |= DRIVER_ATOMIC;

	dev = drm_dev_alloc(&kms_driver, &pdev->dev);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	ret = pci_enable_device(pdev);
	if (ret)
		goto err_free;

	dev->pdev = pdev;

	pci_set_drvdata(pdev, dev);

retry_init:
	ret = drm_dev_register(dev, ent->driver_data);
	if (ret == -EAGAIN && ++retry <= 3) {
		DRM_INFO("retry init %d\n", retry);
		/* Don't request EX mode too frequently which is attacking */
		msleep(5000);
		goto retry_init;
	} else if (ret)
		goto err_pci;

	return 0;

err_pci:
	pci_disable_device(pdev);
err_free:
	drm_dev_put(dev);
	return ret;
}