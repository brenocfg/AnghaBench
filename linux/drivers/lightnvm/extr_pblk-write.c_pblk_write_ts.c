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
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int pblk_submit_write (struct pblk*,int*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

int pblk_write_ts(void *data)
{
	struct pblk *pblk = data;
	int secs_left;
	int write_failure = 0;

	while (!kthread_should_stop()) {
		if (!write_failure) {
			write_failure = pblk_submit_write(pblk, &secs_left);

			if (secs_left)
				continue;
		}
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	}

	return 0;
}