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
struct drm_device {struct arcpgu_drm_private* dev_private; } ;
struct arcpgu_drm_private {int /*<<< orphan*/  fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fbdev_cma_hotplug_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcpgu_fb_output_poll_changed(struct drm_device *dev)
{
	struct arcpgu_drm_private *arcpgu = dev->dev_private;

	drm_fbdev_cma_hotplug_event(arcpgu->fbdev);
}