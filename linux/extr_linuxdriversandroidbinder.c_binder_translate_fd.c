#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct binder_transaction {int flags; TYPE_2__* buffer; struct binder_proc* to_proc; } ;
struct binder_thread {int /*<<< orphan*/  pid; struct binder_proc* proc; } ;
struct binder_proc {int /*<<< orphan*/  tsk; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {TYPE_1__* target_node; } ;
struct TYPE_3__ {int accept_fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_TRANSACTION ; 
 int EBADF ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int TF_ACCEPT_FDS ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int security_binder_transfer_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  task_fd_install (struct binder_proc*,int,struct file*) ; 
 int task_get_unused_fd_flags (struct binder_proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_binder_transaction_fd (struct binder_transaction*,int,int) ; 

__attribute__((used)) static int binder_translate_fd(int fd,
			       struct binder_transaction *t,
			       struct binder_thread *thread,
			       struct binder_transaction *in_reply_to)
{
	struct binder_proc *proc = thread->proc;
	struct binder_proc *target_proc = t->to_proc;
	int target_fd;
	struct file *file;
	int ret;
	bool target_allows_fd;

	if (in_reply_to)
		target_allows_fd = !!(in_reply_to->flags & TF_ACCEPT_FDS);
	else
		target_allows_fd = t->buffer->target_node->accept_fds;
	if (!target_allows_fd) {
		binder_user_error("%d:%d got %s with fd, %d, but target does not allow fds\n",
				  proc->pid, thread->pid,
				  in_reply_to ? "reply" : "transaction",
				  fd);
		ret = -EPERM;
		goto err_fd_not_accepted;
	}

	file = fget(fd);
	if (!file) {
		binder_user_error("%d:%d got transaction with invalid fd, %d\n",
				  proc->pid, thread->pid, fd);
		ret = -EBADF;
		goto err_fget;
	}
	ret = security_binder_transfer_file(proc->tsk, target_proc->tsk, file);
	if (ret < 0) {
		ret = -EPERM;
		goto err_security;
	}

	target_fd = task_get_unused_fd_flags(target_proc, O_CLOEXEC);
	if (target_fd < 0) {
		ret = -ENOMEM;
		goto err_get_unused_fd;
	}
	task_fd_install(target_proc, target_fd, file);
	trace_binder_transaction_fd(t, fd, target_fd);
	binder_debug(BINDER_DEBUG_TRANSACTION, "        fd %d -> %d\n",
		     fd, target_fd);

	return target_fd;

err_get_unused_fd:
err_security:
	fput(file);
err_fget:
err_fd_not_accepted:
	return ret;
}