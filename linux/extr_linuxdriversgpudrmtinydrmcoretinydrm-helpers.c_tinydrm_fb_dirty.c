#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_plane {int /*<<< orphan*/  mutex; TYPE_2__* state; } ;
struct TYPE_4__ {struct drm_plane plane; } ;
struct tinydrm_device {int (* fb_dirty ) (struct drm_framebuffer*,struct drm_file*,unsigned int,unsigned int,struct drm_clip_rect*,unsigned int) ;int /*<<< orphan*/  dirty_lock; TYPE_1__ pipe; } ;
struct drm_framebuffer {TYPE_3__* dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; struct tinydrm_device* dev_private; } ;
struct TYPE_5__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct drm_framebuffer*,struct drm_file*,unsigned int,unsigned int,struct drm_clip_rect*,unsigned int) ; 

int tinydrm_fb_dirty(struct drm_framebuffer *fb,
		     struct drm_file *file_priv,
		     unsigned int flags, unsigned int color,
		     struct drm_clip_rect *clips,
		     unsigned int num_clips)
{
	struct tinydrm_device *tdev = fb->dev->dev_private;
	struct drm_plane *plane = &tdev->pipe.plane;
	int ret = 0;

	drm_modeset_lock(&plane->mutex, NULL);

	/* fbdev can flush even when we're not interested */
	if (plane->state->fb == fb) {
		mutex_lock(&tdev->dirty_lock);
		ret = tdev->fb_dirty(fb, file_priv, flags,
				     color, clips, num_clips);
		mutex_unlock(&tdev->dirty_lock);
	}

	drm_modeset_unlock(&plane->mutex);

	if (ret)
		dev_err_once(fb->dev->dev,
			     "Failed to update display %d\n", ret);

	return ret;
}