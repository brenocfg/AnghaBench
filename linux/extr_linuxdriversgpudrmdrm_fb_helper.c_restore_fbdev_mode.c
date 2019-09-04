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
struct drm_fb_helper {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int restore_fbdev_mode_atomic (struct drm_fb_helper*,int) ; 
 int restore_fbdev_mode_legacy (struct drm_fb_helper*) ; 

__attribute__((used)) static int restore_fbdev_mode(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;

	if (drm_drv_uses_atomic_modeset(dev))
		return restore_fbdev_mode_atomic(fb_helper, true);
	else
		return restore_fbdev_mode_legacy(fb_helper);
}