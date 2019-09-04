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
typedef  int /*<<< orphan*/  uint32_t ;
struct qxl_device {int /*<<< orphan*/  surf_id_idr_lock; int /*<<< orphan*/  surf_id_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void qxl_surface_id_dealloc(struct qxl_device *qdev,
			    uint32_t surface_id)
{
	spin_lock(&qdev->surf_id_idr_lock);
	idr_remove(&qdev->surf_id_idr, surface_id);
	spin_unlock(&qdev->surf_id_idr_lock);
}