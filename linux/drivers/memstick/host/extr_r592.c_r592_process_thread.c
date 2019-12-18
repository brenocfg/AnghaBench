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
struct r592_device {int /*<<< orphan*/  io_thread_lock; int /*<<< orphan*/  req; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENXIO ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 scalar_t__ kthread_should_stop () ; 
 int memstick_next_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r592_execute_tpc (struct r592_device*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int r592_process_thread(void *data)
{
	int error;
	struct r592_device *dev = (struct r592_device *)data;
	unsigned long flags;

	while (!kthread_should_stop()) {
		spin_lock_irqsave(&dev->io_thread_lock, flags);
		set_current_state(TASK_INTERRUPTIBLE);
		error = memstick_next_req(dev->host, &dev->req);
		spin_unlock_irqrestore(&dev->io_thread_lock, flags);

		if (error) {
			if (error == -ENXIO || error == -EAGAIN) {
				dbg_verbose("IO: done IO, sleeping");
			} else {
				dbg("IO: unknown error from "
					"memstick_next_req %d", error);
			}

			if (kthread_should_stop())
				set_current_state(TASK_RUNNING);

			schedule();
		} else {
			set_current_state(TASK_RUNNING);
			r592_execute_tpc(dev);
		}
	}
	return 0;
}