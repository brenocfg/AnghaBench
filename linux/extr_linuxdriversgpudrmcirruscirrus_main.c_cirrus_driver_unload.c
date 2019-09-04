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
struct drm_device {struct cirrus_device* dev_private; } ;
struct cirrus_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cirrus_device_fini (struct cirrus_device*) ; 
 int /*<<< orphan*/  cirrus_mm_fini (struct cirrus_device*) ; 
 int /*<<< orphan*/  cirrus_modeset_fini (struct cirrus_device*) ; 
 int /*<<< orphan*/  kfree (struct cirrus_device*) ; 

void cirrus_driver_unload(struct drm_device *dev)
{
	struct cirrus_device *cdev = dev->dev_private;

	if (cdev == NULL)
		return;
	cirrus_modeset_fini(cdev);
	cirrus_mm_fini(cdev);
	cirrus_device_fini(cdev);
	kfree(cdev);
	dev->dev_private = NULL;
}