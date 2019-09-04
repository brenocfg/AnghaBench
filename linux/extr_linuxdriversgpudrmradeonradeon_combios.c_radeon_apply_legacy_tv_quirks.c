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
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */

__attribute__((used)) static bool radeon_apply_legacy_tv_quirks(struct drm_device *dev)
{
	/* Acer 5102 has non-existent TV port */
	if (dev->pdev->device == 0x5975 &&
	    dev->pdev->subsystem_vendor == 0x1025 &&
	    dev->pdev->subsystem_device == 0x009f)
		return false;

	/* HP dc5750 has non-existent TV port */
	if (dev->pdev->device == 0x5974 &&
	    dev->pdev->subsystem_vendor == 0x103c &&
	    dev->pdev->subsystem_device == 0x280a)
		return false;

	/* MSI S270 has non-existent TV port */
	if (dev->pdev->device == 0x5955 &&
	    dev->pdev->subsystem_vendor == 0x1462 &&
	    dev->pdev->subsystem_device == 0x0131)
		return false;

	return true;
}