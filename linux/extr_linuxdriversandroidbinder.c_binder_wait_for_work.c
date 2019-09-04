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
struct binder_thread {int /*<<< orphan*/  wait; int /*<<< orphan*/  waiting_thread_node; struct binder_proc* proc; } ;
struct binder_proc {int /*<<< orphan*/  waiting_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ binder_has_work_ilocked (struct binder_thread*,int) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (struct binder_proc*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezer_count () ; 
 int /*<<< orphan*/  freezer_do_not_count () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int binder_wait_for_work(struct binder_thread *thread,
				bool do_proc_work)
{
	DEFINE_WAIT(wait);
	struct binder_proc *proc = thread->proc;
	int ret = 0;

	freezer_do_not_count();
	binder_inner_proc_lock(proc);
	for (;;) {
		prepare_to_wait(&thread->wait, &wait, TASK_INTERRUPTIBLE);
		if (binder_has_work_ilocked(thread, do_proc_work))
			break;
		if (do_proc_work)
			list_add(&thread->waiting_thread_node,
				 &proc->waiting_threads);
		binder_inner_proc_unlock(proc);
		schedule();
		binder_inner_proc_lock(proc);
		list_del_init(&thread->waiting_thread_node);
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
	}
	finish_wait(&thread->wait, &wait);
	binder_inner_proc_unlock(proc);
	freezer_count();

	return ret;
}