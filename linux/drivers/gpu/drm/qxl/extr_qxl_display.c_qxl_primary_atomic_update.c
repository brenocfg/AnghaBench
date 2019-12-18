#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct qxl_device {TYPE_2__* dumb_heads; scalar_t__ primary_bo; } ;
struct qxl_bo {scalar_t__ is_dumb; int /*<<< orphan*/  is_primary; struct qxl_bo* shadow; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_4__* state; TYPE_1__* dev; } ;
struct drm_clip_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * obj; } ;
struct TYPE_9__ {TYPE_5__* fb; TYPE_3__* crtc; } ;
struct TYPE_8__ {size_t index; } ;
struct TYPE_7__ {int /*<<< orphan*/  x; } ;
struct TYPE_6__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_draw_dirty_fb (struct qxl_device*,TYPE_5__*,struct qxl_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_clip_rect*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_io_create_primary (struct qxl_device*,struct qxl_bo*) ; 
 int /*<<< orphan*/  qxl_io_destroy_primary (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_primary_apply_cursor (struct drm_plane*) ; 

__attribute__((used)) static void qxl_primary_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct qxl_device *qdev = plane->dev->dev_private;
	struct qxl_bo *bo = gem_to_qxl_bo(plane->state->fb->obj[0]);
	struct qxl_bo *primary;
	struct drm_clip_rect norect = {
	    .x1 = 0,
	    .y1 = 0,
	    .x2 = plane->state->fb->width,
	    .y2 = plane->state->fb->height
	};
	uint32_t dumb_shadow_offset = 0;

	primary = bo->shadow ? bo->shadow : bo;

	if (!primary->is_primary) {
		if (qdev->primary_bo)
			qxl_io_destroy_primary(qdev);
		qxl_io_create_primary(qdev, primary);
		qxl_primary_apply_cursor(plane);
	}

	if (bo->is_dumb)
		dumb_shadow_offset =
			qdev->dumb_heads[plane->state->crtc->index].x;

	qxl_draw_dirty_fb(qdev, plane->state->fb, bo, 0, 0, &norect, 1, 1,
			  dumb_shadow_offset);
}