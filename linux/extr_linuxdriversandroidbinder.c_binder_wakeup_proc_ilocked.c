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
struct binder_thread {int dummy; } ;
struct binder_proc {int dummy; } ;

/* Variables and functions */
 struct binder_thread* binder_select_thread_ilocked (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_wakeup_thread_ilocked (struct binder_proc*,struct binder_thread*,int) ; 

__attribute__((used)) static void binder_wakeup_proc_ilocked(struct binder_proc *proc)
{
	struct binder_thread *thread = binder_select_thread_ilocked(proc);

	binder_wakeup_thread_ilocked(proc, thread, /* sync = */false);
}