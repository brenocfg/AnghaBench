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
struct TYPE_2__ {scalar_t__ count; } ;
struct drm_device {int dummy; } ;
struct udl_device {TYPE_1__ urbs; int /*<<< orphan*/  udev; int /*<<< orphan*/  gem_lock; struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_TRANSFER ; 
 int /*<<< orphan*/  WRITES_IN_FLIGHT ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udl_alloc_urb_list (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udl_fbdev_init (struct drm_device*) ; 
 int /*<<< orphan*/  udl_free_urb_list (struct drm_device*) ; 
 int udl_modeset_init (struct drm_device*) ; 
 int /*<<< orphan*/  udl_parse_vendor_descriptor (struct drm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ udl_select_std_channel (struct udl_device*) ; 

int udl_init(struct udl_device *udl)
{
	struct drm_device *dev = &udl->drm;
	int ret = -ENOMEM;

	DRM_DEBUG("\n");

	mutex_init(&udl->gem_lock);

	if (!udl_parse_vendor_descriptor(dev, udl->udev)) {
		ret = -ENODEV;
		DRM_ERROR("firmware not recognized. Assume incompatible device\n");
		goto err;
	}

	if (udl_select_std_channel(udl))
		DRM_ERROR("Selecting channel failed\n");

	if (!udl_alloc_urb_list(dev, WRITES_IN_FLIGHT, MAX_TRANSFER)) {
		DRM_ERROR("udl_alloc_urb_list failed\n");
		goto err;
	}

	DRM_DEBUG("\n");
	ret = udl_modeset_init(dev);
	if (ret)
		goto err;

	ret = udl_fbdev_init(dev);
	if (ret)
		goto err;

	drm_kms_helper_poll_init(dev);

	return 0;

err:
	if (udl->urbs.count)
		udl_free_urb_list(dev);
	DRM_ERROR("%d\n", ret);
	return ret;
}