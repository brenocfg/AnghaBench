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
struct qxl_device {int /*<<< orphan*/  surf_evict_mutex; } ;
struct qxl_bo {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qxl_bo_reserve (struct qxl_bo*,int) ; 
 int /*<<< orphan*/  qxl_bo_unreserve (struct qxl_bo*) ; 
 int /*<<< orphan*/  qxl_surface_evict_locked (struct qxl_device*,struct qxl_bo*,int) ; 
 int ttm_bo_wait (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int qxl_reap_surf(struct qxl_device *qdev, struct qxl_bo *surf, bool stall)
{
	int ret;

	ret = qxl_bo_reserve(surf, false);
	if (ret)
		return ret;

	if (stall)
		mutex_unlock(&qdev->surf_evict_mutex);

	ret = ttm_bo_wait(&surf->tbo, true, !stall);

	if (stall)
		mutex_lock(&qdev->surf_evict_mutex);
	if (ret) {
		qxl_bo_unreserve(surf);
		return ret;
	}

	qxl_surface_evict_locked(qdev, surf, true);
	qxl_bo_unreserve(surf);
	return 0;
}