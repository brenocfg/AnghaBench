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
struct task_struct {TYPE_1__* io_context; } ;
struct TYPE_2__ {int ioprio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPRIO_CLASS_NONE ; 
 int /*<<< orphan*/  IOPRIO_NORM ; 
 int IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int security_task_getioprio (struct task_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int get_task_ioprio(struct task_struct *p)
{
	int ret;

	ret = security_task_getioprio(p);
	if (ret)
		goto out;
	ret = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_NONE, IOPRIO_NORM);
	task_lock(p);
	if (p->io_context)
		ret = p->io_context->ioprio;
	task_unlock(p);
out:
	return ret;
}