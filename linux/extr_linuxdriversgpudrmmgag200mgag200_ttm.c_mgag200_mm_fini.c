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
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct mga_device {scalar_t__ fb_mtrr; TYPE_1__ ttm; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_io_free_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_del (scalar_t__) ; 
 int /*<<< orphan*/  mgag200_ttm_global_release (struct mga_device*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void mgag200_mm_fini(struct mga_device *mdev)
{
	struct drm_device *dev = mdev->dev;

	ttm_bo_device_release(&mdev->ttm.bdev);

	mgag200_ttm_global_release(mdev);

	arch_io_free_memtype_wc(pci_resource_start(dev->pdev, 0),
				pci_resource_len(dev->pdev, 0));
	arch_phys_wc_del(mdev->fb_mtrr);
	mdev->fb_mtrr = 0;
}