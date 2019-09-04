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
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  ds_wait ; 
 int /*<<< orphan*/  ds_work_list ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_ds_work () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int ds_thread(void *__unused)
{
	DEFINE_WAIT(wait);

	while (1) {
		prepare_to_wait(&ds_wait, &wait, TASK_INTERRUPTIBLE);
		if (list_empty(&ds_work_list))
			schedule();
		finish_wait(&ds_wait, &wait);

		if (kthread_should_stop())
			break;

		process_ds_work();
	}

	return 0;
}