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
struct udl_device {int /*<<< orphan*/ * fbdev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct udl_device* to_udl (struct drm_device*) ; 
 int /*<<< orphan*/  udl_fbdev_destroy (struct drm_device*,int /*<<< orphan*/ *) ; 

void udl_fbdev_cleanup(struct drm_device *dev)
{
	struct udl_device *udl = to_udl(dev);
	if (!udl->fbdev)
		return;

	udl_fbdev_destroy(dev, udl->fbdev);
	kfree(udl->fbdev);
	udl->fbdev = NULL;
}