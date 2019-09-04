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
struct drbd_work_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb; } ;
struct completion_work {int /*<<< orphan*/  done; TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_queue_work (struct drbd_work_queue*,TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w_complete ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void drbd_flush_workqueue(struct drbd_work_queue *work_queue)
{
	struct completion_work completion_work;

	completion_work.w.cb = w_complete;
	init_completion(&completion_work.done);
	drbd_queue_work(work_queue, &completion_work.w);
	wait_for_completion(&completion_work.done);
}