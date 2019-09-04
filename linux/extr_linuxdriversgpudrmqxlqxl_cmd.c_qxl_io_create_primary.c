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
struct qxl_surface_create {int /*<<< orphan*/  type; int /*<<< orphan*/  flags; struct qxl_device* mem; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct qxl_device {int primary_created; TYPE_2__* ram_header; } ;
struct TYPE_3__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct qxl_bo {TYPE_2__* kptr; struct qxl_bo* shadow; TYPE_1__ surf; } ;
struct TYPE_4__ {struct qxl_surface_create create_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,struct qxl_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  QXL_IO_CREATE_PRIMARY_ASYNC ; 
 int /*<<< orphan*/  QXL_SURF_FLAG_KEEP_DATA ; 
 int /*<<< orphan*/  QXL_SURF_TYPE_PRIMARY ; 
 void* qxl_bo_physical_address (struct qxl_device*,struct qxl_bo*,unsigned int) ; 
 int /*<<< orphan*/  wait_for_io_cmd (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qxl_io_create_primary(struct qxl_device *qdev,
			   unsigned offset, struct qxl_bo *bo)
{
	struct qxl_surface_create *create;

	DRM_DEBUG_DRIVER("qdev %p, ram_header %p\n", qdev, qdev->ram_header);
	create = &qdev->ram_header->create_surface;
	create->format = bo->surf.format;
	create->width = bo->surf.width;
	create->height = bo->surf.height;
	create->stride = bo->surf.stride;
	if (bo->shadow) {
		create->mem = qxl_bo_physical_address(qdev, bo->shadow, offset);
	} else {
		create->mem = qxl_bo_physical_address(qdev, bo, offset);
	}

	DRM_DEBUG_DRIVER("mem = %llx, from %p\n", create->mem, bo->kptr);

	create->flags = QXL_SURF_FLAG_KEEP_DATA;
	create->type = QXL_SURF_TYPE_PRIMARY;

	wait_for_io_cmd(qdev, 0, QXL_IO_CREATE_PRIMARY_ASYNC);
	qdev->primary_created = true;
}