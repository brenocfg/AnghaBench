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
struct binder_proc {int /*<<< orphan*/  tmp_ref; int /*<<< orphan*/  threads; scalar_t__ is_dead; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_free_proc (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (struct binder_proc*) ; 

__attribute__((used)) static void binder_proc_dec_tmpref(struct binder_proc *proc)
{
	binder_inner_proc_lock(proc);
	proc->tmp_ref--;
	if (proc->is_dead && RB_EMPTY_ROOT(&proc->threads) &&
			!proc->tmp_ref) {
		binder_inner_proc_unlock(proc);
		binder_free_proc(proc);
		return;
	}
	binder_inner_proc_unlock(proc);
}