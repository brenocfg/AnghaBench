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
struct qxl_device {TYPE_2__* primary_bo; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int is_primary; TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_IO_DESTROY_PRIMARY_ASYNC ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_io_cmd (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qxl_io_destroy_primary(struct qxl_device *qdev)
{
	wait_for_io_cmd(qdev, 0, QXL_IO_DESTROY_PRIMARY_ASYNC);
	qdev->primary_bo->is_primary = false;
	drm_gem_object_put_unlocked(&qdev->primary_bo->tbo.base);
	qdev->primary_bo = NULL;
}