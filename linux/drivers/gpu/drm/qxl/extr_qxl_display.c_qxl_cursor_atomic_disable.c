#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qxl_release {int dummy; } ;
struct qxl_device {int dummy; } ;
struct qxl_cursor_cmd {int /*<<< orphan*/  release_info; int /*<<< orphan*/  type; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_2__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_CMD_CURSOR ; 
 int /*<<< orphan*/  QXL_CURSOR_HIDE ; 
 int /*<<< orphan*/  QXL_RELEASE_CURSOR_CMD ; 
 int qxl_alloc_release_reserved (struct qxl_device*,int,int /*<<< orphan*/ ,struct qxl_release**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_push_cursor_ring_release (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_release_fence_buffer_objects (struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_free (struct qxl_device*,struct qxl_release*) ; 
 scalar_t__ qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_reserve_list (struct qxl_release*,int) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qxl_cursor_atomic_disable(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct qxl_device *qdev = plane->dev->dev_private;
	struct qxl_release *release;
	struct qxl_cursor_cmd *cmd;
	int ret;

	ret = qxl_alloc_release_reserved(qdev, sizeof(*cmd),
					 QXL_RELEASE_CURSOR_CMD,
					 &release, NULL);
	if (ret)
		return;

	ret = qxl_release_reserve_list(release, true);
	if (ret) {
		qxl_release_free(qdev, release);
		return;
	}

	cmd = (struct qxl_cursor_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_CURSOR_HIDE;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_push_cursor_ring_release(qdev, release, QXL_CMD_CURSOR, false);
	qxl_release_fence_buffer_objects(release);
}