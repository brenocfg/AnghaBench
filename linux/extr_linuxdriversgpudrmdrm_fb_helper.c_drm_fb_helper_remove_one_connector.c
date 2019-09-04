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
struct drm_fb_helper {int /*<<< orphan*/  lock; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int __drm_fb_helper_remove_one_connector (struct drm_fb_helper*,struct drm_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_fb_helper_remove_one_connector(struct drm_fb_helper *fb_helper,
				       struct drm_connector *connector)
{
	int err;

	if (!fb_helper)
		return 0;

	mutex_lock(&fb_helper->lock);
	err = __drm_fb_helper_remove_one_connector(fb_helper, connector);
	mutex_unlock(&fb_helper->lock);

	return err;
}