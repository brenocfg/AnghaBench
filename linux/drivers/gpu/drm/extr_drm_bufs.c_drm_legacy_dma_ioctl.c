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
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* dma_ioctl ) (struct drm_device*,void*,struct drm_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_device*,void*,struct drm_file*) ; 

int drm_legacy_dma_ioctl(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	if (!drm_core_check_feature(dev, DRIVER_LEGACY))
		return -EOPNOTSUPP;

	if (dev->driver->dma_ioctl)
		return dev->driver->dma_ioctl(dev, data, file_priv);
	else
		return -EINVAL;
}