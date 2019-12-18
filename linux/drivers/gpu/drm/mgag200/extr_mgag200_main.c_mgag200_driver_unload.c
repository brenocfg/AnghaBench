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
struct mga_device {int dummy; } ;
struct drm_device {struct mga_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  mgag200_mm_fini (struct mga_device*) ; 
 int /*<<< orphan*/  mgag200_modeset_fini (struct mga_device*) ; 

void mgag200_driver_unload(struct drm_device *dev)
{
	struct mga_device *mdev = dev->dev_private;

	if (mdev == NULL)
		return;
	mgag200_modeset_fini(mdev);
	drm_mode_config_cleanup(dev);
	mgag200_mm_fini(mdev);
	dev->dev_private = NULL;
}