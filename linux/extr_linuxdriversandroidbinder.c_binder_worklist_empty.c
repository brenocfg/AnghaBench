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
struct list_head {int dummy; } ;
struct binder_proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_inner_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (struct binder_proc*) ; 
 int binder_worklist_empty_ilocked (struct list_head*) ; 

__attribute__((used)) static bool binder_worklist_empty(struct binder_proc *proc,
				  struct list_head *list)
{
	bool ret;

	binder_inner_proc_lock(proc);
	ret = binder_worklist_empty_ilocked(list);
	binder_inner_proc_unlock(proc);
	return ret;
}