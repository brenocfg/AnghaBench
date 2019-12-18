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
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int xb_init_comms () ; 
 int /*<<< orphan*/  xenwatch_thread ; 
 int /*<<< orphan*/  xs_reboot_nb ; 
 int /*<<< orphan*/  xs_reset_watches () ; 

int xs_init(void)
{
	int err;
	struct task_struct *task;

	register_reboot_notifier(&xs_reboot_nb);

	/* Initialize the shared memory rings to talk to xenstored */
	err = xb_init_comms();
	if (err)
		return err;

	task = kthread_run(xenwatch_thread, NULL, "xenwatch");
	if (IS_ERR(task))
		return PTR_ERR(task);

	/* shutdown watches for kexec boot */
	xs_reset_watches();

	return 0;
}