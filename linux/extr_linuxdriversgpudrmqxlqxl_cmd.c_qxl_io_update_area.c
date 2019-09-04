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
typedef  scalar_t__ uint32_t ;
struct qxl_rect {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
struct qxl_device {int /*<<< orphan*/  update_area_mutex; TYPE_2__* ram_header; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct qxl_bo {int surface_id; TYPE_1__ surf; scalar_t__ is_primary; int /*<<< orphan*/  hw_surf_alloc; } ;
struct TYPE_4__ {int update_surface; struct qxl_rect update_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QXL_IO_UPDATE_AREA_ASYNC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_io_cmd_user (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int qxl_io_update_area(struct qxl_device *qdev, struct qxl_bo *surf,
			const struct qxl_rect *area)
{
	int surface_id;
	uint32_t surface_width, surface_height;
	int ret;

	if (!surf->hw_surf_alloc)
		DRM_ERROR("got io update area with no hw surface\n");

	if (surf->is_primary)
		surface_id = 0;
	else
		surface_id = surf->surface_id;
	surface_width = surf->surf.width;
	surface_height = surf->surf.height;

	if (area->left < 0 || area->top < 0 ||
	    area->right > surface_width || area->bottom > surface_height)
		return -EINVAL;

	mutex_lock(&qdev->update_area_mutex);
	qdev->ram_header->update_area = *area;
	qdev->ram_header->update_surface = surface_id;
	ret = wait_for_io_cmd_user(qdev, 0, QXL_IO_UPDATE_AREA_ASYNC, true);
	mutex_unlock(&qdev->update_area_mutex);
	return ret;
}