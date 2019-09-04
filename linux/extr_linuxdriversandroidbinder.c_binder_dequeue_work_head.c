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
struct binder_work {int dummy; } ;
struct binder_proc {int dummy; } ;

/* Variables and functions */
 struct binder_work* binder_dequeue_work_head_ilocked (struct list_head*) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (struct binder_proc*) ; 

__attribute__((used)) static struct binder_work *binder_dequeue_work_head(
					struct binder_proc *proc,
					struct list_head *list)
{
	struct binder_work *w;

	binder_inner_proc_lock(proc);
	w = binder_dequeue_work_head_ilocked(list);
	binder_inner_proc_unlock(proc);
	return w;
}