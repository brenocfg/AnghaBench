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
struct binder_thread {int /*<<< orphan*/  proc; int /*<<< orphan*/  tmp_ref; scalar_t__ is_dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_free_thread (struct binder_thread*) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void binder_thread_dec_tmpref(struct binder_thread *thread)
{
	/*
	 * atomic is used to protect the counter value while
	 * it cannot reach zero or thread->is_dead is false
	 */
	binder_inner_proc_lock(thread->proc);
	atomic_dec(&thread->tmp_ref);
	if (thread->is_dead && !atomic_read(&thread->tmp_ref)) {
		binder_inner_proc_unlock(thread->proc);
		binder_free_thread(thread);
		return;
	}
	binder_inner_proc_unlock(thread->proc);
}