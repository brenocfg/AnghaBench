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
struct qxl_surface_cmd {int surface_id; int /*<<< orphan*/  release_info; int /*<<< orphan*/  type; } ;
struct qxl_release {int surface_release_id; } ;
struct qxl_device {int /*<<< orphan*/  surf_id_idr_lock; int /*<<< orphan*/  surf_id_idr; } ;
struct qxl_bo {int hw_surf_alloc; int surface_id; int /*<<< orphan*/ * surf_create; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_CMD_SURFACE ; 
 int /*<<< orphan*/  QXL_SURFACE_CMD_DESTROY ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int qxl_alloc_surface_release_reserved (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qxl_release**) ; 
 int /*<<< orphan*/  qxl_push_command_ring_release (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_release_fence_buffer_objects (struct qxl_release*) ; 
 scalar_t__ qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int qxl_hw_surface_dealloc(struct qxl_device *qdev,
			   struct qxl_bo *surf)
{
	struct qxl_surface_cmd *cmd;
	struct qxl_release *release;
	int ret;
	int id;

	if (!surf->hw_surf_alloc)
		return 0;

	ret = qxl_alloc_surface_release_reserved(qdev, QXL_SURFACE_CMD_DESTROY,
						 surf->surf_create,
						 &release);
	if (ret)
		return ret;

	surf->surf_create = NULL;
	/* remove the surface from the idr, but not the surface id yet */
	spin_lock(&qdev->surf_id_idr_lock);
	idr_replace(&qdev->surf_id_idr, NULL, surf->surface_id);
	spin_unlock(&qdev->surf_id_idr_lock);
	surf->hw_surf_alloc = false;

	id = surf->surface_id;
	surf->surface_id = 0;

	release->surface_release_id = id;
	cmd = (struct qxl_surface_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_SURFACE_CMD_DESTROY;
	cmd->surface_id = id;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_push_command_ring_release(qdev, release, QXL_CMD_SURFACE, false);

	qxl_release_fence_buffer_objects(release);

	return 0;
}