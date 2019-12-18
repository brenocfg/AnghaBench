#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__* pdev; void* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_FLAG_NEVER_SKIP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 unsigned long RADEON_IS_AGP ; 
 unsigned long RADEON_IS_IGP ; 
 unsigned long RADEON_IS_PCI ; 
 unsigned long RADEON_IS_PCIE ; 
 unsigned long RADEON_IS_PX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_capability (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_is_thunderbolt_attached (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ ) ; 
 int radeon_acpi_init (struct radeon_device*) ; 
 int radeon_device_init (struct radeon_device*,struct drm_device*,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  radeon_driver_unload_kms (struct drm_device*) ; 
 scalar_t__ radeon_has_atpx () ; 
 scalar_t__ radeon_is_px (struct drm_device*) ; 
 int radeon_modeset_init (struct radeon_device*) ; 
 scalar_t__ radeon_runtime_pm ; 

int radeon_driver_load_kms(struct drm_device *dev, unsigned long flags)
{
	struct radeon_device *rdev;
	int r, acpi_status;

	rdev = kzalloc(sizeof(struct radeon_device), GFP_KERNEL);
	if (rdev == NULL) {
		return -ENOMEM;
	}
	dev->dev_private = (void *)rdev;

	/* update BUS flag */
	if (pci_find_capability(dev->pdev, PCI_CAP_ID_AGP)) {
		flags |= RADEON_IS_AGP;
	} else if (pci_is_pcie(dev->pdev)) {
		flags |= RADEON_IS_PCIE;
	} else {
		flags |= RADEON_IS_PCI;
	}

	if ((radeon_runtime_pm != 0) &&
	    radeon_has_atpx() &&
	    ((flags & RADEON_IS_IGP) == 0) &&
	    !pci_is_thunderbolt_attached(dev->pdev))
		flags |= RADEON_IS_PX;

	/* radeon_device_init should report only fatal error
	 * like memory allocation failure or iomapping failure,
	 * or memory manager initialization failure, it must
	 * properly initialize the GPU MC controller and permit
	 * VRAM allocation
	 */
	r = radeon_device_init(rdev, dev, dev->pdev, flags);
	if (r) {
		dev_err(&dev->pdev->dev, "Fatal error during GPU init\n");
		goto out;
	}

	/* Again modeset_init should fail only on fatal error
	 * otherwise it should provide enough functionalities
	 * for shadowfb to run
	 */
	r = radeon_modeset_init(rdev);
	if (r)
		dev_err(&dev->pdev->dev, "Fatal error during modeset init\n");

	/* Call ACPI methods: require modeset init
	 * but failure is not fatal
	 */
	if (!r) {
		acpi_status = radeon_acpi_init(rdev);
		if (acpi_status)
		dev_dbg(&dev->pdev->dev,
				"Error during ACPI methods call\n");
	}

	if (radeon_is_px(dev)) {
		dev_pm_set_driver_flags(dev->dev, DPM_FLAG_NEVER_SKIP);
		pm_runtime_use_autosuspend(dev->dev);
		pm_runtime_set_autosuspend_delay(dev->dev, 5000);
		pm_runtime_set_active(dev->dev);
		pm_runtime_allow(dev->dev);
		pm_runtime_mark_last_busy(dev->dev);
		pm_runtime_put_autosuspend(dev->dev);
	}

out:
	if (r)
		radeon_driver_unload_kms(dev);


	return r;
}