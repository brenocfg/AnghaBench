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
struct genwqe_dev {int /*<<< orphan*/  queue_waitq; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 scalar_t__ GENWQE_POLLING_ENABLED ; 
 int HZ ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  genwqe_check_ddcb_queue (struct genwqe_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ genwqe_ddcbs_in_flight (struct genwqe_dev*) ; 
 scalar_t__ genwqe_next_ddcb_ready (struct genwqe_dev*) ; 
 int kthread_should_stop () ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int genwqe_card_thread(void *data)
{
	int should_stop = 0, rc = 0;
	struct genwqe_dev *cd = (struct genwqe_dev *)data;

	while (!kthread_should_stop()) {

		genwqe_check_ddcb_queue(cd, &cd->queue);

		if (GENWQE_POLLING_ENABLED) {
			rc = wait_event_interruptible_timeout(
				cd->queue_waitq,
				genwqe_ddcbs_in_flight(cd) ||
				(should_stop = kthread_should_stop()), 1);
		} else {
			rc = wait_event_interruptible_timeout(
				cd->queue_waitq,
				genwqe_next_ddcb_ready(cd) ||
				(should_stop = kthread_should_stop()), HZ);
		}
		if (should_stop)
			break;

		/*
		 * Avoid soft lockups on heavy loads; we do not want
		 * to disable our interrupts.
		 */
		cond_resched();
	}
	return 0;
}