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
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* firstopen ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_legacy_dma_setup (struct drm_device*) ; 
 int stub1 (struct drm_device*) ; 

int drm_legacy_setup(struct drm_device * dev)
{
	int ret;

	if (dev->driver->firstopen &&
	    drm_core_check_feature(dev, DRIVER_LEGACY)) {
		ret = dev->driver->firstopen(dev);
		if (ret != 0)
			return ret;
	}

	ret = drm_legacy_dma_setup(dev);
	if (ret < 0)
		return ret;


	DRM_DEBUG("\n");
	return 0;
}