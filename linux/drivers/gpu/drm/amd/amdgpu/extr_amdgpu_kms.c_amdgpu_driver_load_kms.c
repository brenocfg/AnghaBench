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
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__* pdev; void* dev_private; } ;
struct amdgpu_device {scalar_t__ rmmio; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long AMD_IS_APU ; 
 unsigned long AMD_IS_PX ; 
 int /*<<< orphan*/  DPM_FLAG_NEVER_SKIP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amdgpu_acpi_init (struct amdgpu_device*) ; 
 int amdgpu_device_init (struct amdgpu_device*,struct drm_device*,TYPE_1__*,unsigned long) ; 
 scalar_t__ amdgpu_device_is_px (struct drm_device*) ; 
 int /*<<< orphan*/  amdgpu_driver_unload_kms (struct drm_device*) ; 
 scalar_t__ amdgpu_has_atpx () ; 
 scalar_t__ amdgpu_has_atpx_dgpu_power_cntl () ; 
 scalar_t__ amdgpu_is_atpx_hybrid () ; 
 scalar_t__ amdgpu_runtime_pm ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_thunderbolt_attached (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ ) ; 

int amdgpu_driver_load_kms(struct drm_device *dev, unsigned long flags)
{
	struct amdgpu_device *adev;
	int r, acpi_status;

	adev = kzalloc(sizeof(struct amdgpu_device), GFP_KERNEL);
	if (adev == NULL) {
		return -ENOMEM;
	}
	dev->dev_private = (void *)adev;

	if ((amdgpu_runtime_pm != 0) &&
	    amdgpu_has_atpx() &&
	    (amdgpu_is_atpx_hybrid() ||
	     amdgpu_has_atpx_dgpu_power_cntl()) &&
	    ((flags & AMD_IS_APU) == 0) &&
	    !pci_is_thunderbolt_attached(dev->pdev))
		flags |= AMD_IS_PX;

	/* amdgpu_device_init should report only fatal error
	 * like memory allocation failure or iomapping failure,
	 * or memory manager initialization failure, it must
	 * properly initialize the GPU MC controller and permit
	 * VRAM allocation
	 */
	r = amdgpu_device_init(adev, dev, dev->pdev, flags);
	if (r) {
		dev_err(&dev->pdev->dev, "Fatal error during GPU init\n");
		goto out;
	}

	/* Call ACPI methods: require modeset init
	 * but failure is not fatal
	 */
	if (!r) {
		acpi_status = amdgpu_acpi_init(adev);
		if (acpi_status)
			dev_dbg(&dev->pdev->dev,
				"Error during ACPI methods call\n");
	}

	if (amdgpu_device_is_px(dev)) {
		dev_pm_set_driver_flags(dev->dev, DPM_FLAG_NEVER_SKIP);
		pm_runtime_use_autosuspend(dev->dev);
		pm_runtime_set_autosuspend_delay(dev->dev, 5000);
		pm_runtime_set_active(dev->dev);
		pm_runtime_allow(dev->dev);
		pm_runtime_mark_last_busy(dev->dev);
		pm_runtime_put_autosuspend(dev->dev);
	}

out:
	if (r) {
		/* balance pm_runtime_get_sync in amdgpu_driver_unload_kms */
		if (adev->rmmio && amdgpu_device_is_px(dev))
			pm_runtime_put_noidle(dev->dev);
		amdgpu_driver_unload_kms(dev);
	}

	return r;
}