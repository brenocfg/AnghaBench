#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qxl_release {int dummy; } ;
struct qxl_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {int visible; int /*<<< orphan*/  shape; TYPE_1__ position; } ;
struct TYPE_8__ {TYPE_3__ set; } ;
struct qxl_cursor_cmd {int /*<<< orphan*/  release_info; TYPE_4__ u; int /*<<< orphan*/  type; } ;
struct qxl_crtc {int /*<<< orphan*/  cursor_bo; } ;
struct drm_plane {TYPE_2__* state; struct drm_device* dev; } ;
struct drm_framebuffer {scalar_t__ hot_y; scalar_t__ hot_x; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct TYPE_6__ {scalar_t__ crtc_y; scalar_t__ crtc_x; int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_CMD_CURSOR ; 
 int /*<<< orphan*/  QXL_CURSOR_SET ; 
 int /*<<< orphan*/  QXL_RELEASE_CURSOR_CMD ; 
 int qxl_alloc_release_reserved (struct qxl_device*,int,int /*<<< orphan*/ ,struct qxl_release**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_bo_physical_address (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_push_cursor_ring_release (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_release_fence_buffer_objects (struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_free (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_list_add (struct qxl_release*,int /*<<< orphan*/ ) ; 
 scalar_t__ qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_reserve_list (struct qxl_release*,int) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ *) ; 
 struct qxl_crtc* to_qxl_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qxl_primary_apply_cursor(struct drm_plane *plane)
{
	struct drm_device *dev = plane->dev;
	struct qxl_device *qdev = dev->dev_private;
	struct drm_framebuffer *fb = plane->state->fb;
	struct qxl_crtc *qcrtc = to_qxl_crtc(plane->state->crtc);
	struct qxl_cursor_cmd *cmd;
	struct qxl_release *release;
	int ret = 0;

	if (!qcrtc->cursor_bo)
		return 0;

	ret = qxl_alloc_release_reserved(qdev, sizeof(*cmd),
					 QXL_RELEASE_CURSOR_CMD,
					 &release, NULL);
	if (ret)
		return ret;

	ret = qxl_release_list_add(release, qcrtc->cursor_bo);
	if (ret)
		goto out_free_release;

	ret = qxl_release_reserve_list(release, false);
	if (ret)
		goto out_free_release;

	cmd = (struct qxl_cursor_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_CURSOR_SET;
	cmd->u.set.position.x = plane->state->crtc_x + fb->hot_x;
	cmd->u.set.position.y = plane->state->crtc_y + fb->hot_y;

	cmd->u.set.shape = qxl_bo_physical_address(qdev, qcrtc->cursor_bo, 0);

	cmd->u.set.visible = 1;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_push_cursor_ring_release(qdev, release, QXL_CMD_CURSOR, false);
	qxl_release_fence_buffer_objects(release);

	return ret;

out_free_release:
	qxl_release_free(qdev, release);
	return ret;
}