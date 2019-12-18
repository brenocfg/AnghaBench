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
struct drm_device {struct amdgpu_device* dev_private; int /*<<< orphan*/  dev; } ;
struct amdgpu_device {int /*<<< orphan*/ * rmmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_acpi_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_fini (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_device_is_px (struct drm_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_unregister_gpu_instance (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_request_full_gpu (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

void amdgpu_driver_unload_kms(struct drm_device *dev)
{
	struct amdgpu_device *adev = dev->dev_private;

	if (adev == NULL)
		return;

	amdgpu_unregister_gpu_instance(adev);

	if (adev->rmmio == NULL)
		goto done_free;

	if (amdgpu_sriov_vf(adev))
		amdgpu_virt_request_full_gpu(adev, false);

	if (amdgpu_device_is_px(dev)) {
		pm_runtime_get_sync(dev->dev);
		pm_runtime_forbid(dev->dev);
	}

	amdgpu_acpi_fini(adev);

	amdgpu_device_fini(adev);

done_free:
	kfree(adev);
	dev->dev_private = NULL;
}