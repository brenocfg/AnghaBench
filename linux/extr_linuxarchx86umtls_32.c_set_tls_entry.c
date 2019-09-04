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
struct user_desc {int dummy; } ;
struct TYPE_3__ {TYPE_2__* tls_array; } ;
struct thread_struct {TYPE_1__ arch; } ;
struct task_struct {struct thread_struct thread; } ;
struct TYPE_4__ {int present; int flushed; struct user_desc tls; } ;

/* Variables and functions */
 int EINVAL ; 
 int GDT_ENTRY_TLS_MAX ; 
 int GDT_ENTRY_TLS_MIN ; 

__attribute__((used)) static int set_tls_entry(struct task_struct* task, struct user_desc *info,
			 int idx, int flushed)
{
	struct thread_struct *t = &task->thread;

	if (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
		return -EINVAL;

	t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].tls = *info;
	t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].present = 1;
	t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].flushed = flushed;

	return 0;
}