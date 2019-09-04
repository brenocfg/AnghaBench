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
struct tinydrm_device {struct drm_device* drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_fbdev_generic_setup (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tinydrm_register(struct tinydrm_device *tdev)
{
	struct drm_device *drm = tdev->drm;
	int ret;

	ret = drm_dev_register(tdev->drm, 0);
	if (ret)
		return ret;

	ret = drm_fbdev_generic_setup(drm, 0);
	if (ret)
		DRM_ERROR("Failed to initialize fbdev: %d\n", ret);

	return 0;
}