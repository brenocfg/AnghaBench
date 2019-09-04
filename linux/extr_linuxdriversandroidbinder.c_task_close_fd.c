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
struct binder_proc {int /*<<< orphan*/  files_lock; int /*<<< orphan*/ * files; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTARTNOHAND ; 
 int ERESTARTNOINTR ; 
 int ERESTARTSYS ; 
 int ERESTART_RESTARTBLOCK ; 
 int ESRCH ; 
 int __close_fd (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long task_close_fd(struct binder_proc *proc, unsigned int fd)
{
	int retval;

	mutex_lock(&proc->files_lock);
	if (proc->files == NULL) {
		retval = -ESRCH;
		goto err;
	}
	retval = __close_fd(proc->files, fd);
	/* can't restart close syscall because file table entry was cleared */
	if (unlikely(retval == -ERESTARTSYS ||
		     retval == -ERESTARTNOINTR ||
		     retval == -ERESTARTNOHAND ||
		     retval == -ERESTART_RESTARTBLOCK))
		retval = -EINTR;
err:
	mutex_unlock(&proc->files_lock);
	return retval;
}