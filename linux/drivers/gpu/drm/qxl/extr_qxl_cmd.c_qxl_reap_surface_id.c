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
struct qxl_device {int last_alloced_surf_id; int /*<<< orphan*/  surf_evict_mutex; int /*<<< orphan*/  surf_id_idr_lock; int /*<<< orphan*/  surf_id_idr; TYPE_1__* rom; } ;
struct TYPE_2__ {int n_surfaces; } ;

/* Variables and functions */
 void* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_queue_garbage_collect (struct qxl_device*,int) ; 
 int qxl_reap_surf (struct qxl_device*,void*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qxl_reap_surface_id(struct qxl_device *qdev, int max_to_reap)
{
	int num_reaped = 0;
	int i, ret;
	bool stall = false;
	int start = 0;

	mutex_lock(&qdev->surf_evict_mutex);
again:

	spin_lock(&qdev->surf_id_idr_lock);
	start = qdev->last_alloced_surf_id + 1;
	spin_unlock(&qdev->surf_id_idr_lock);

	for (i = start; i < start + qdev->rom->n_surfaces; i++) {
		void *objptr;
		int surfid = i % qdev->rom->n_surfaces;

		/* this avoids the case where the objects is in the
		   idr but has been evicted half way - its makes
		   the idr lookup atomic with the eviction */
		spin_lock(&qdev->surf_id_idr_lock);
		objptr = idr_find(&qdev->surf_id_idr, surfid);
		spin_unlock(&qdev->surf_id_idr_lock);

		if (!objptr)
			continue;

		ret = qxl_reap_surf(qdev, objptr, stall);
		if (ret == 0)
			num_reaped++;
		if (num_reaped >= max_to_reap)
			break;
	}
	if (num_reaped == 0 && stall == false) {
		stall = true;
		goto again;
	}

	mutex_unlock(&qdev->surf_evict_mutex);
	if (num_reaped) {
		usleep_range(500, 1000);
		qxl_queue_garbage_collect(qdev, true);
	}

	return 0;
}