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
struct task_struct {int dummy; } ;
struct rc_dev {TYPE_1__* raw; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; struct task_struct* thread; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  ir_raw_client_list ; 
 int /*<<< orphan*/  ir_raw_event_thread ; 
 int /*<<< orphan*/  ir_raw_handler_lock ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ir_raw_event_register(struct rc_dev *dev)
{
	struct task_struct *thread;

	thread = kthread_run(ir_raw_event_thread, dev->raw, "rc%u", dev->minor);
	if (IS_ERR(thread))
		return PTR_ERR(thread);

	dev->raw->thread = thread;

	mutex_lock(&ir_raw_handler_lock);
	list_add_tail(&dev->raw->list, &ir_raw_client_list);
	mutex_unlock(&ir_raw_handler_lock);

	return 0;
}