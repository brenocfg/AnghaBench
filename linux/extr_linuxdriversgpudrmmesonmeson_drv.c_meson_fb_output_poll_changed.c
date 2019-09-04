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
struct meson_drm {int /*<<< orphan*/  fbdev; } ;
struct drm_device {struct meson_drm* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fbdev_cma_hotplug_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_fb_output_poll_changed(struct drm_device *dev)
{
	struct meson_drm *priv = dev->dev_private;

	drm_fbdev_cma_hotplug_event(priv->fbdev);
}