#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qxl_device {int dummy; } ;
struct qxl_bo {int is_primary; TYPE_1__* shadow; } ;
struct drm_framebuffer {TYPE_2__* dev; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * obj; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; scalar_t__ y1; scalar_t__ x1; } ;
struct TYPE_5__ {struct qxl_device* dev_private; } ;
struct TYPE_4__ {int is_primary; } ;

/* Variables and functions */
 unsigned int DRM_MODE_FB_DIRTY_ANNOTATE_COPY ; 
 int /*<<< orphan*/  drm_modeset_lock_all (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (TYPE_2__*) ; 
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_draw_dirty_fb (struct qxl_device*,struct drm_framebuffer*,struct qxl_bo*,unsigned int,unsigned int,struct drm_clip_rect*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qxl_framebuffer_surface_dirty(struct drm_framebuffer *fb,
					 struct drm_file *file_priv,
					 unsigned int flags, unsigned int color,
					 struct drm_clip_rect *clips,
					 unsigned int num_clips)
{
	/* TODO: vmwgfx where this was cribbed from had locking. Why? */
	struct qxl_device *qdev = fb->dev->dev_private;
	struct drm_clip_rect norect;
	struct qxl_bo *qobj;
	bool is_primary;
	int inc = 1;

	drm_modeset_lock_all(fb->dev);

	qobj = gem_to_qxl_bo(fb->obj[0]);
	/* if we aren't primary surface ignore this */
	is_primary = qobj->shadow ? qobj->shadow->is_primary : qobj->is_primary;
	if (!is_primary) {
		drm_modeset_unlock_all(fb->dev);
		return 0;
	}

	if (!num_clips) {
		num_clips = 1;
		clips = &norect;
		norect.x1 = norect.y1 = 0;
		norect.x2 = fb->width;
		norect.y2 = fb->height;
	} else if (flags & DRM_MODE_FB_DIRTY_ANNOTATE_COPY) {
		num_clips /= 2;
		inc = 2; /* skip source rects */
	}

	qxl_draw_dirty_fb(qdev, fb, qobj, flags, color,
			  clips, num_clips, inc, 0);

	drm_modeset_unlock_all(fb->dev);

	return 0;
}