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
struct ibmvfc_host {int /*<<< orphan*/  work_wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MIN_NICE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ibmvfc_dbg (struct ibmvfc_host*,char*) ; 
 int /*<<< orphan*/  ibmvfc_do_work (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_work_to_do (struct ibmvfc_host*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_work(void *data)
{
	struct ibmvfc_host *vhost = data;
	int rc;

	set_user_nice(current, MIN_NICE);

	while (1) {
		rc = wait_event_interruptible(vhost->work_wait_q,
					      ibmvfc_work_to_do(vhost));

		BUG_ON(rc);

		if (kthread_should_stop())
			break;

		ibmvfc_do_work(vhost);
	}

	ibmvfc_dbg(vhost, "ibmvfc kthread exiting...\n");
	return 0;
}