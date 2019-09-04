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
struct drm_fb_helper {int /*<<< orphan*/ * fbdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  preferred_bpp; scalar_t__ funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_connector; } ;
struct drm_device {TYPE_1__ mode_config; scalar_t__ fb_helper; } ;
struct drm_client_dev {struct drm_device* dev; } ;

/* Variables and functions */
 int drm_fb_helper_fbdev_setup (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_fb_helper* drm_fb_helper_from_client (struct drm_client_dev*) ; 
 int /*<<< orphan*/  drm_fb_helper_generic_funcs ; 
 int drm_fb_helper_hotplug_event (scalar_t__) ; 

__attribute__((used)) static int drm_fbdev_client_hotplug(struct drm_client_dev *client)
{
	struct drm_fb_helper *fb_helper = drm_fb_helper_from_client(client);
	struct drm_device *dev = client->dev;
	int ret;

	/* If drm_fb_helper_fbdev_setup() failed, we only try once */
	if (!fb_helper->dev && fb_helper->funcs)
		return 0;

	if (dev->fb_helper)
		return drm_fb_helper_hotplug_event(dev->fb_helper);

	if (!dev->mode_config.num_connector)
		return 0;

	ret = drm_fb_helper_fbdev_setup(dev, fb_helper, &drm_fb_helper_generic_funcs,
					fb_helper->preferred_bpp, 0);
	if (ret) {
		fb_helper->dev = NULL;
		fb_helper->fbdev = NULL;
		return ret;
	}

	return 0;
}