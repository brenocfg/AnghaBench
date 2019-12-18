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
struct udl_fbdev {int /*<<< orphan*/  helper; } ;
struct udl_device {struct udl_fbdev* fbdev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_unlink_fbi (int /*<<< orphan*/ *) ; 
 struct udl_device* to_udl (struct drm_device*) ; 

void udl_fbdev_unplug(struct drm_device *dev)
{
	struct udl_device *udl = to_udl(dev);
	struct udl_fbdev *ufbdev;
	if (!udl->fbdev)
		return;

	ufbdev = udl->fbdev;
	drm_fb_helper_unlink_fbi(&ufbdev->helper);
}