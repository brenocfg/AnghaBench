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
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct qxl_framebuffer {int /*<<< orphan*/  obj; TYPE_3__ base; } ;
struct qxl_device {int dummy; } ;
struct qxl_bo {scalar_t__ shadow; int is_primary; } ;
struct drm_plane_state {scalar_t__ fb; } ;
struct drm_plane {TYPE_2__* state; TYPE_1__* dev; } ;
struct drm_clip_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_5__ {scalar_t__ fb; } ;
struct TYPE_4__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_draw_dirty_fb (struct qxl_device*,struct qxl_framebuffer*,struct qxl_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_clip_rect*,int,int) ; 
 int /*<<< orphan*/  qxl_io_create_primary (struct qxl_device*,int /*<<< orphan*/ ,struct qxl_bo*) ; 
 int /*<<< orphan*/  qxl_io_destroy_primary (struct qxl_device*) ; 
 int qxl_primary_apply_cursor (struct drm_plane*) ; 
 struct qxl_framebuffer* to_qxl_framebuffer (scalar_t__) ; 

__attribute__((used)) static void qxl_primary_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct qxl_device *qdev = plane->dev->dev_private;
	struct qxl_framebuffer *qfb =
		to_qxl_framebuffer(plane->state->fb);
	struct qxl_framebuffer *qfb_old;
	struct qxl_bo *bo = gem_to_qxl_bo(qfb->obj);
	struct qxl_bo *bo_old;
	struct drm_clip_rect norect = {
	    .x1 = 0,
	    .y1 = 0,
	    .x2 = qfb->base.width,
	    .y2 = qfb->base.height
	};
	int ret;
	bool same_shadow = false;

	if (old_state->fb) {
		qfb_old = to_qxl_framebuffer(old_state->fb);
		bo_old = gem_to_qxl_bo(qfb_old->obj);
	} else {
		bo_old = NULL;
	}

	if (bo == bo_old)
		return;

	if (bo_old && bo_old->shadow && bo->shadow &&
	    bo_old->shadow == bo->shadow) {
		same_shadow = true;
	}

	if (bo_old && bo_old->is_primary) {
		if (!same_shadow)
			qxl_io_destroy_primary(qdev);
		bo_old->is_primary = false;

		ret = qxl_primary_apply_cursor(plane);
		if (ret)
			DRM_ERROR(
			"could not set cursor after creating primary");
	}

	if (!bo->is_primary) {
		if (!same_shadow)
			qxl_io_create_primary(qdev, 0, bo);
		bo->is_primary = true;
	}

	qxl_draw_dirty_fb(qdev, qfb, bo, 0, 0, &norect, 1, 1);
}