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
struct TYPE_2__ {int /*<<< orphan*/  funcs; } ;
struct drm_fb_helper {TYPE_1__ client; } ;
struct drm_device {struct drm_fb_helper* fb_helper; } ;

/* Variables and functions */
 int drm_client_init (struct drm_device*,TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fbdev_emulation ; 

int drm_fb_helper_init(struct drm_device *dev,
		       struct drm_fb_helper *fb_helper,
		       int max_conn_count)
{
	int ret;

	if (!drm_fbdev_emulation) {
		dev->fb_helper = fb_helper;
		return 0;
	}

	/*
	 * If this is not the generic fbdev client, initialize a drm_client
	 * without callbacks so we can use the modesets.
	 */
	if (!fb_helper->client.funcs) {
		ret = drm_client_init(dev, &fb_helper->client, "drm_fb_helper", NULL);
		if (ret)
			return ret;
	}

	dev->fb_helper = fb_helper;

	return 0;
}