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
struct drm_fb_helper {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_client_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fbdev_cleanup (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  kfree (struct drm_fb_helper*) ; 

__attribute__((used)) static void drm_fbdev_release(struct drm_fb_helper *fb_helper)
{
	drm_fbdev_cleanup(fb_helper);
	drm_client_release(&fb_helper->client);
	kfree(fb_helper);
}