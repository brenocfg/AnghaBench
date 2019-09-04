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
struct TYPE_4__ {TYPE_1__* dev; } ;
struct qxl_framebuffer {int /*<<< orphan*/  obj; TYPE_2__ base; } ;
struct qxl_device {int dummy; } ;
struct qxl_bo {int /*<<< orphan*/  is_primary; } ;
struct drm_framebuffer {int /*<<< orphan*/  dev; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; scalar_t__ y1; scalar_t__ x1; } ;
struct TYPE_3__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 unsigned int DRM_MODE_FB_DIRTY_ANNOTATE_COPY ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ ) ; 
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_draw_dirty_fb (struct qxl_device*,struct qxl_framebuffer*,struct qxl_bo*,unsigned int,unsigned int,struct drm_clip_rect*,unsigned int,int) ; 
 struct qxl_framebuffer* to_qxl_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int qxl_framebuffer_surface_dirty(struct drm_framebuffer *fb,
					 struct drm_file *file_priv,
					 unsigned flags, unsigned color,
					 struct drm_clip_rect *clips,
					 unsigned num_clips)
{
	/* TODO: vmwgfx where this was cribbed from had locking. Why? */
	struct qxl_framebuffer *qxl_fb = to_qxl_framebuffer(fb);
	struct qxl_device *qdev = qxl_fb->base.dev->dev_private;
	struct drm_clip_rect norect;
	struct qxl_bo *qobj;
	int inc = 1;

	drm_modeset_lock_all(fb->dev);

	qobj = gem_to_qxl_bo(qxl_fb->obj);
	/* if we aren't primary surface ignore this */
	if (!qobj->is_primary) {
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

	qxl_draw_dirty_fb(qdev, qxl_fb, qobj, flags, color,
			  clips, num_clips, inc);

	drm_modeset_unlock_all(fb->dev);

	return 0;
}