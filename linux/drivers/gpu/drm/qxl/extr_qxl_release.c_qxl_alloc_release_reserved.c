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
union qxl_release_info {int id; } ;
struct qxl_release {int release_offset; struct qxl_bo* release_bo; } ;
struct qxl_device {int* current_release_bo_offset; int /*<<< orphan*/  release_mutex; struct qxl_bo** current_release_bo; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int QXL_RELEASE_CURSOR_CMD ; 
 int QXL_RELEASE_DRAWABLE ; 
 int QXL_RELEASE_SURFACE_CMD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct qxl_bo* qxl_bo_ref (struct qxl_bo*) ; 
 int /*<<< orphan*/  qxl_bo_unref (struct qxl_bo**) ; 
 int qxl_release_alloc (struct qxl_device*,int,struct qxl_release**) ; 
 int qxl_release_bo_alloc (struct qxl_device*,struct qxl_bo**) ; 
 int /*<<< orphan*/  qxl_release_free (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_list_add (struct qxl_release*,struct qxl_bo*) ; 
 union qxl_release_info* qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,union qxl_release_info*) ; 
 int* release_size_per_bo ; 
 int* releases_per_bo ; 

int qxl_alloc_release_reserved(struct qxl_device *qdev, unsigned long size,
				       int type, struct qxl_release **release,
				       struct qxl_bo **rbo)
{
	struct qxl_bo *bo;
	int idr_ret;
	int ret = 0;
	union qxl_release_info *info;
	int cur_idx;

	if (type == QXL_RELEASE_DRAWABLE)
		cur_idx = 0;
	else if (type == QXL_RELEASE_SURFACE_CMD)
		cur_idx = 1;
	else if (type == QXL_RELEASE_CURSOR_CMD)
		cur_idx = 2;
	else {
		DRM_ERROR("got illegal type: %d\n", type);
		return -EINVAL;
	}

	idr_ret = qxl_release_alloc(qdev, type, release);
	if (idr_ret < 0) {
		if (rbo)
			*rbo = NULL;
		return idr_ret;
	}

	mutex_lock(&qdev->release_mutex);
	if (qdev->current_release_bo_offset[cur_idx] + 1 >= releases_per_bo[cur_idx]) {
		qxl_bo_unref(&qdev->current_release_bo[cur_idx]);
		qdev->current_release_bo_offset[cur_idx] = 0;
		qdev->current_release_bo[cur_idx] = NULL;
	}
	if (!qdev->current_release_bo[cur_idx]) {
		ret = qxl_release_bo_alloc(qdev, &qdev->current_release_bo[cur_idx]);
		if (ret) {
			mutex_unlock(&qdev->release_mutex);
			qxl_release_free(qdev, *release);
			return ret;
		}
	}

	bo = qxl_bo_ref(qdev->current_release_bo[cur_idx]);

	(*release)->release_bo = bo;
	(*release)->release_offset = qdev->current_release_bo_offset[cur_idx] * release_size_per_bo[cur_idx];
	qdev->current_release_bo_offset[cur_idx]++;

	if (rbo)
		*rbo = bo;

	mutex_unlock(&qdev->release_mutex);

	ret = qxl_release_list_add(*release, bo);
	qxl_bo_unref(&bo);
	if (ret) {
		qxl_release_free(qdev, *release);
		return ret;
	}

	info = qxl_release_map(qdev, *release);
	info->id = idr_ret;
	qxl_release_unmap(qdev, *release, info);

	return ret;
}