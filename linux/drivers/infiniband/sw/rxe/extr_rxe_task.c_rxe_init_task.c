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
struct rxe_task {int (* func ) (void*) ;int destroyed; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  name; void* arg; void* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_STATE_START ; 
 int /*<<< orphan*/  rxe_do_task ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int rxe_init_task(void *obj, struct rxe_task *task,
		  void *arg, int (*func)(void *), char *name)
{
	task->obj	= obj;
	task->arg	= arg;
	task->func	= func;
	snprintf(task->name, sizeof(task->name), "%s", name);
	task->destroyed	= false;

	tasklet_init(&task->tasklet, rxe_do_task, (unsigned long)task);

	task->state = TASK_STATE_START;
	spin_lock_init(&task->state_lock);

	return 0;
}