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
struct qxl_device {int dummy; } ;
struct qxl_bo {scalar_t__ type; scalar_t__ surface_id; } ;

/* Variables and functions */
 scalar_t__ QXL_GEM_DOMAIN_SURFACE ; 
 int qxl_hw_surface_alloc (struct qxl_device*,struct qxl_bo*) ; 
 int qxl_surface_id_alloc (struct qxl_device*,struct qxl_bo*) ; 

int qxl_bo_check_id(struct qxl_device *qdev, struct qxl_bo *bo)
{
	int ret;

	if (bo->type == QXL_GEM_DOMAIN_SURFACE && bo->surface_id == 0) {
		/* allocate a surface id for this surface now */
		ret = qxl_surface_id_alloc(qdev, bo);
		if (ret)
			return ret;

		ret = qxl_hw_surface_alloc(qdev, bo);
		if (ret)
			return ret;
	}
	return 0;
}