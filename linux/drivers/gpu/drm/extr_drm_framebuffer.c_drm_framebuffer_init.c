#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_framebuffer_funcs {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/  head; int /*<<< orphan*/  comm; struct drm_framebuffer_funcs const* funcs; int /*<<< orphan*/  filp_head; int /*<<< orphan*/  format; struct drm_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  fb_lock; int /*<<< orphan*/  fb_list; int /*<<< orphan*/  num_fb; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_FB ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __drm_mode_object_add (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  drm_framebuffer_free ; 
 int /*<<< orphan*/  drm_mode_object_register (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_framebuffer_init(struct drm_device *dev, struct drm_framebuffer *fb,
			 const struct drm_framebuffer_funcs *funcs)
{
	int ret;

	if (WARN_ON_ONCE(fb->dev != dev || !fb->format))
		return -EINVAL;

	INIT_LIST_HEAD(&fb->filp_head);

	fb->funcs = funcs;
	strcpy(fb->comm, current->comm);

	ret = __drm_mode_object_add(dev, &fb->base, DRM_MODE_OBJECT_FB,
				    false, drm_framebuffer_free);
	if (ret)
		goto out;

	mutex_lock(&dev->mode_config.fb_lock);
	dev->mode_config.num_fb++;
	list_add(&fb->head, &dev->mode_config.fb_list);
	mutex_unlock(&dev->mode_config.fb_lock);

	drm_mode_object_register(dev, &fb->base);
out:
	return ret;
}