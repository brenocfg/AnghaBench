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
struct drm_fb_helper {unsigned int preferred_bpp; int /*<<< orphan*/  client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_client_add (int /*<<< orphan*/ *) ; 
 int drm_client_init (struct drm_device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fbdev_client_funcs ; 
 int /*<<< orphan*/  drm_fbdev_client_hotplug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fbdev_emulation ; 
 int /*<<< orphan*/  kfree (struct drm_fb_helper*) ; 
 struct drm_fb_helper* kzalloc (int,int /*<<< orphan*/ ) ; 

int drm_fbdev_generic_setup(struct drm_device *dev, unsigned int preferred_bpp)
{
	struct drm_fb_helper *fb_helper;
	int ret;

	if (!drm_fbdev_emulation)
		return 0;

	fb_helper = kzalloc(sizeof(*fb_helper), GFP_KERNEL);
	if (!fb_helper)
		return -ENOMEM;

	ret = drm_client_init(dev, &fb_helper->client, "fbdev", &drm_fbdev_client_funcs);
	if (ret) {
		kfree(fb_helper);
		return ret;
	}

	drm_client_add(&fb_helper->client);

	fb_helper->preferred_bpp = preferred_bpp;

	drm_fbdev_client_hotplug(&fb_helper->client);

	return 0;
}