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
typedef  void* uint32_t ;
struct qxl_device {int /*<<< orphan*/  surf_id_idr_lock; void* last_alloced_surf_id; int /*<<< orphan*/  surf_id_idr; TYPE_1__* rom; } ;
struct qxl_bo {void* surface_id; } ;
struct TYPE_2__ {void* n_surfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  qxl_reap_surface_id (struct qxl_device*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int qxl_surface_id_alloc(struct qxl_device *qdev,
		      struct qxl_bo *surf)
{
	uint32_t handle;
	int idr_ret;
	int count = 0;
again:
	idr_preload(GFP_ATOMIC);
	spin_lock(&qdev->surf_id_idr_lock);
	idr_ret = idr_alloc(&qdev->surf_id_idr, NULL, 1, 0, GFP_NOWAIT);
	spin_unlock(&qdev->surf_id_idr_lock);
	idr_preload_end();
	if (idr_ret < 0)
		return idr_ret;
	handle = idr_ret;

	if (handle >= qdev->rom->n_surfaces) {
		count++;
		spin_lock(&qdev->surf_id_idr_lock);
		idr_remove(&qdev->surf_id_idr, handle);
		spin_unlock(&qdev->surf_id_idr_lock);
		qxl_reap_surface_id(qdev, 2);
		goto again;
	}
	surf->surface_id = handle;

	spin_lock(&qdev->surf_id_idr_lock);
	qdev->last_alloced_surf_id = handle;
	spin_unlock(&qdev->surf_id_idr_lock);
	return 0;
}