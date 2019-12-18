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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int) ; 
 int process_msg () ; 
 int process_writes () ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_thread_work () ; 
 int /*<<< orphan*/  xb_waitq ; 
 int /*<<< orphan*/ * xenbus_task ; 

__attribute__((used)) static int xenbus_thread(void *unused)
{
	int err;

	while (!kthread_should_stop()) {
		if (wait_event_interruptible(xb_waitq, xb_thread_work()))
			continue;

		err = process_msg();
		if (err == -ENOMEM)
			schedule();
		else if (err)
			pr_warn_ratelimited("error %d while reading message\n",
					    err);

		err = process_writes();
		if (err)
			pr_warn_ratelimited("error %d while writing message\n",
					    err);
	}

	xenbus_task = NULL;
	return 0;
}