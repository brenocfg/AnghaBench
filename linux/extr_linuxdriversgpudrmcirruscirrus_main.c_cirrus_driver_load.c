#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct drm_device {TYPE_2__* pdev; TYPE_1__ mode_config; void* dev_private; } ;
struct cirrus_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cirrus_device_init (struct cirrus_device*,struct drm_device*,TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  cirrus_driver_unload (struct drm_device*) ; 
 int cirrus_mm_init (struct cirrus_device*) ; 
 int /*<<< orphan*/  cirrus_mode_funcs ; 
 int cirrus_modeset_init (struct cirrus_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct cirrus_device* kzalloc (int,int /*<<< orphan*/ ) ; 

int cirrus_driver_load(struct drm_device *dev, unsigned long flags)
{
	struct cirrus_device *cdev;
	int r;

	cdev = kzalloc(sizeof(struct cirrus_device), GFP_KERNEL);
	if (cdev == NULL)
		return -ENOMEM;
	dev->dev_private = (void *)cdev;

	r = cirrus_device_init(cdev, dev, dev->pdev, flags);
	if (r) {
		dev_err(&dev->pdev->dev, "Fatal error during GPU init: %d\n", r);
		goto out;
	}

	r = cirrus_mm_init(cdev);
	if (r) {
		dev_err(&dev->pdev->dev, "fatal err on mm init\n");
		goto out;
	}

	/*
	 * cirrus_modeset_init() is initializing/registering the emulated fbdev
	 * and DRM internals can access/test some of the fields in
	 * mode_config->funcs as part of the fbdev registration process.
	 * Make sure dev->mode_config.funcs is properly set to avoid
	 * dereferencing a NULL pointer.
	 * FIXME: mode_config.funcs assignment should probably be done in
	 * cirrus_modeset_init() (that's a common pattern seen in other DRM
	 * drivers).
	 */
	dev->mode_config.funcs = &cirrus_mode_funcs;
	r = cirrus_modeset_init(cdev);
	if (r) {
		dev_err(&dev->pdev->dev, "Fatal error during modeset init: %d\n", r);
		goto out;
	}

	return 0;
out:
	cirrus_driver_unload(dev);
	return r;
}