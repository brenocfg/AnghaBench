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
struct qxl_device {int /*<<< orphan*/  gc_work; int /*<<< orphan*/  release_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_check_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

bool qxl_queue_garbage_collect(struct qxl_device *qdev, bool flush)
{
	if (!qxl_check_idle(qdev->release_ring)) {
		schedule_work(&qdev->gc_work);
		if (flush)
			flush_work(&qdev->gc_work);
		return true;
	}
	return false;
}