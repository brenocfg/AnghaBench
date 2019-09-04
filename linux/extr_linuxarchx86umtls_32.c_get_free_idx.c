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
struct TYPE_4__ {TYPE_1__* tls_array; } ;
struct thread_struct {TYPE_2__ arch; } ;
struct task_struct {struct thread_struct thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int ESRCH ; 
 int GDT_ENTRY_TLS_ENTRIES ; 
 int GDT_ENTRY_TLS_MIN ; 

__attribute__((used)) static int get_free_idx(struct task_struct* task)
{
	struct thread_struct *t = &task->thread;
	int idx;

	if (!t->arch.tls_array)
		return GDT_ENTRY_TLS_MIN;

	for (idx = 0; idx < GDT_ENTRY_TLS_ENTRIES; idx++)
		if (!t->arch.tls_array[idx].present)
			return idx + GDT_ENTRY_TLS_MIN;
	return -ESRCH;
}