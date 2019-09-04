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
struct drm_fb_helper {scalar_t__ dev; scalar_t__ fbdev; } ;
struct drm_client_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_client_release (struct drm_client_dev*) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 struct drm_fb_helper* drm_fb_helper_from_client (struct drm_client_dev*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  kfree (struct drm_fb_helper*) ; 

__attribute__((used)) static void drm_fbdev_client_unregister(struct drm_client_dev *client)
{
	struct drm_fb_helper *fb_helper = drm_fb_helper_from_client(client);

	if (fb_helper->fbdev) {
		drm_fb_helper_unregister_fbi(fb_helper);
		/* drm_fbdev_fb_destroy() takes care of cleanup */
		return;
	}

	/* Did drm_fb_helper_fbdev_setup() run? */
	if (fb_helper->dev)
		drm_fb_helper_fini(fb_helper);

	drm_client_release(client);
	kfree(fb_helper);
}