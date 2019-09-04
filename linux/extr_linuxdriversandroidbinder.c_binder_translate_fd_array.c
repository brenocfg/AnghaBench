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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct binder_transaction {struct binder_proc* to_proc; } ;
struct binder_thread {int /*<<< orphan*/  pid; struct binder_proc* proc; } ;
struct binder_proc {int /*<<< orphan*/  pid; int /*<<< orphan*/  alloc; } ;
struct binder_fd_array_object {int num_fds; scalar_t__ parent_offset; } ;
struct binder_buffer_object {scalar_t__ length; uintptr_t buffer; } ;
typedef  scalar_t__ binder_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 int SIZE_MAX ; 
 uintptr_t binder_alloc_get_user_buffer_offset (int /*<<< orphan*/ *) ; 
 int binder_translate_fd (int,struct binder_transaction*,struct binder_thread*,struct binder_transaction*) ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  task_close_fd (struct binder_proc*,int) ; 

__attribute__((used)) static int binder_translate_fd_array(struct binder_fd_array_object *fda,
				     struct binder_buffer_object *parent,
				     struct binder_transaction *t,
				     struct binder_thread *thread,
				     struct binder_transaction *in_reply_to)
{
	binder_size_t fdi, fd_buf_size, num_installed_fds;
	int target_fd;
	uintptr_t parent_buffer;
	u32 *fd_array;
	struct binder_proc *proc = thread->proc;
	struct binder_proc *target_proc = t->to_proc;

	fd_buf_size = sizeof(u32) * fda->num_fds;
	if (fda->num_fds >= SIZE_MAX / sizeof(u32)) {
		binder_user_error("%d:%d got transaction with invalid number of fds (%lld)\n",
				  proc->pid, thread->pid, (u64)fda->num_fds);
		return -EINVAL;
	}
	if (fd_buf_size > parent->length ||
	    fda->parent_offset > parent->length - fd_buf_size) {
		/* No space for all file descriptors here. */
		binder_user_error("%d:%d not enough space to store %lld fds in buffer\n",
				  proc->pid, thread->pid, (u64)fda->num_fds);
		return -EINVAL;
	}
	/*
	 * Since the parent was already fixed up, convert it
	 * back to the kernel address space to access it
	 */
	parent_buffer = parent->buffer -
		binder_alloc_get_user_buffer_offset(&target_proc->alloc);
	fd_array = (u32 *)(parent_buffer + (uintptr_t)fda->parent_offset);
	if (!IS_ALIGNED((unsigned long)fd_array, sizeof(u32))) {
		binder_user_error("%d:%d parent offset not aligned correctly.\n",
				  proc->pid, thread->pid);
		return -EINVAL;
	}
	for (fdi = 0; fdi < fda->num_fds; fdi++) {
		target_fd = binder_translate_fd(fd_array[fdi], t, thread,
						in_reply_to);
		if (target_fd < 0)
			goto err_translate_fd_failed;
		fd_array[fdi] = target_fd;
	}
	return 0;

err_translate_fd_failed:
	/*
	 * Failed to allocate fd or security error, free fds
	 * installed so far.
	 */
	num_installed_fds = fdi;
	for (fdi = 0; fdi < num_installed_fds; fdi++)
		task_close_fd(target_proc, fd_array[fdi]);
	return target_fd;
}