#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_reg {int start; size_t mem_type; } ;
struct TYPE_11__ {int data; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct TYPE_12__ {TYPE_5__ surface_create; } ;
struct qxl_surface_cmd {int /*<<< orphan*/  release_info; int /*<<< orphan*/  surface_id; TYPE_6__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct qxl_release {int dummy; } ;
struct qxl_memslot {int high_bits; } ;
struct qxl_device {int main_mem_slot; int surfaces_mem_slot; int /*<<< orphan*/  surf_id_idr_lock; int /*<<< orphan*/  surf_id_idr; struct qxl_memslot* mem_slots; } ;
struct TYPE_10__ {TYPE_3__* bdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct qxl_bo {int hw_surf_alloc; scalar_t__ type; int /*<<< orphan*/  surface_id; struct qxl_release* surf_create; TYPE_4__ tbo; TYPE_1__ surf; } ;
struct TYPE_9__ {TYPE_2__* man; } ;
struct TYPE_8__ {int gpu_offset; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  QXL_CMD_SURFACE ; 
 scalar_t__ QXL_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  QXL_SURFACE_CMD_CREATE ; 
 int /*<<< orphan*/  QXL_SURF_FLAG_KEEP_DATA ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct qxl_bo*,int /*<<< orphan*/ ) ; 
 int qxl_alloc_surface_release_reserved (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qxl_release**) ; 
 int qxl_bo_physical_address (struct qxl_device*,struct qxl_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_push_command_ring_release (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_release_fence_buffer_objects (struct qxl_release*) ; 
 scalar_t__ qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_reserve_list (struct qxl_release*,int) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int qxl_hw_surface_alloc(struct qxl_device *qdev,
			 struct qxl_bo *surf,
			 struct ttm_mem_reg *new_mem)
{
	struct qxl_surface_cmd *cmd;
	struct qxl_release *release;
	int ret;

	if (surf->hw_surf_alloc)
		return 0;

	ret = qxl_alloc_surface_release_reserved(qdev, QXL_SURFACE_CMD_CREATE,
						 NULL,
						 &release);
	if (ret)
		return ret;

	ret = qxl_release_reserve_list(release, true);
	if (ret)
		return ret;

	cmd = (struct qxl_surface_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_SURFACE_CMD_CREATE;
	cmd->flags = QXL_SURF_FLAG_KEEP_DATA;
	cmd->u.surface_create.format = surf->surf.format;
	cmd->u.surface_create.width = surf->surf.width;
	cmd->u.surface_create.height = surf->surf.height;
	cmd->u.surface_create.stride = surf->surf.stride;
	if (new_mem) {
		int slot_id = surf->type == QXL_GEM_DOMAIN_VRAM ? qdev->main_mem_slot : qdev->surfaces_mem_slot;
		struct qxl_memslot *slot = &(qdev->mem_slots[slot_id]);

		/* TODO - need to hold one of the locks to read tbo.offset */
		cmd->u.surface_create.data = slot->high_bits;

		cmd->u.surface_create.data |= (new_mem->start << PAGE_SHIFT) + surf->tbo.bdev->man[new_mem->mem_type].gpu_offset;
	} else
		cmd->u.surface_create.data = qxl_bo_physical_address(qdev, surf, 0);
	cmd->surface_id = surf->surface_id;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	surf->surf_create = release;

	/* no need to add a release to the fence for this surface bo,
	   since it is only released when we ask to destroy the surface
	   and it would never signal otherwise */
	qxl_push_command_ring_release(qdev, release, QXL_CMD_SURFACE, false);
	qxl_release_fence_buffer_objects(release);

	surf->hw_surf_alloc = true;
	spin_lock(&qdev->surf_id_idr_lock);
	idr_replace(&qdev->surf_id_idr, surf, surf->surface_id);
	spin_unlock(&qdev->surf_id_idr_lock);
	return 0;
}