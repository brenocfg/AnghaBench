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
struct binder_proc {int /*<<< orphan*/  files_lock; int /*<<< orphan*/ * files; int /*<<< orphan*/  tsk; } ;

/* Variables and functions */
 int EMFILE ; 
 int ESRCH ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int __alloc_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  lock_task_sighand (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long task_rlimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int task_get_unused_fd_flags(struct binder_proc *proc, int flags)
{
	unsigned long rlim_cur;
	unsigned long irqs;
	int ret;

	mutex_lock(&proc->files_lock);
	if (proc->files == NULL) {
		ret = -ESRCH;
		goto err;
	}
	if (!lock_task_sighand(proc->tsk, &irqs)) {
		ret = -EMFILE;
		goto err;
	}
	rlim_cur = task_rlimit(proc->tsk, RLIMIT_NOFILE);
	unlock_task_sighand(proc->tsk, &irqs);

	ret = __alloc_fd(proc->files, 0, rlim_cur, flags);
err:
	mutex_unlock(&proc->files_lock);
	return ret;
}