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
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_surface_evict_locked (struct qxl_device*,struct qxl_bo*,int) ; 

void qxl_surface_evict(struct qxl_device *qdev, struct qxl_bo *surf, bool do_update_area)
{
	mutex_lock(&qdev->surf_evict_mutex);
	qxl_surface_evict_locked(qdev, surf, do_update_area);
	mutex_unlock(&qdev->surf_evict_mutex);
}