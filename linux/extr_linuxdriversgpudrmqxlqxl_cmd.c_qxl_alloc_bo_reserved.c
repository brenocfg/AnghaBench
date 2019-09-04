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
struct qxl_release {int dummy; } ;
struct qxl_device {int dummy; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  QXL_GEM_DOMAIN_VRAM ; 
 int qxl_bo_create (struct qxl_device*,unsigned long,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qxl_bo**) ; 
 int /*<<< orphan*/  qxl_bo_unref (struct qxl_bo**) ; 
 int qxl_release_list_add (struct qxl_release*,struct qxl_bo*) ; 

int qxl_alloc_bo_reserved(struct qxl_device *qdev,
			  struct qxl_release *release,
			  unsigned long size,
			  struct qxl_bo **_bo)
{
	struct qxl_bo *bo;
	int ret;

	ret = qxl_bo_create(qdev, size, false /* not kernel - device */,
			    false, QXL_GEM_DOMAIN_VRAM, NULL, &bo);
	if (ret) {
		DRM_ERROR("failed to allocate VRAM BO\n");
		return ret;
	}
	ret = qxl_release_list_add(release, bo);
	if (ret)
		goto out_unref;

	*_bo = bo;
	return 0;
out_unref:
	qxl_bo_unref(&bo);
	return ret;
}