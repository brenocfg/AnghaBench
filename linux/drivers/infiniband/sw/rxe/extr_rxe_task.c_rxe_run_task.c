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
struct rxe_task {int /*<<< orphan*/  tasklet; scalar_t__ destroyed; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_do_task (unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void rxe_run_task(struct rxe_task *task, int sched)
{
	if (task->destroyed)
		return;

	if (sched)
		tasklet_schedule(&task->tasklet);
	else
		rxe_do_task((unsigned long)task);
}