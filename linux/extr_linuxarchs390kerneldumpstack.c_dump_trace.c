#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  dump_trace_func_t ;
struct TYPE_2__ {unsigned long async_stack; } ;

/* Variables and functions */
 unsigned long ASYNC_SIZE ; 
 TYPE_1__ S390_lowcore ; 
 int STACK_FRAME_OVERHEAD ; 
 unsigned long THREAD_SIZE ; 
 unsigned long __dump_trace (int /*<<< orphan*/ ,void*,unsigned long,unsigned long,unsigned long) ; 
 struct task_struct* current ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

void dump_trace(dump_trace_func_t func, void *data, struct task_struct *task,
		unsigned long sp)
{
	unsigned long frame_size;

	frame_size = STACK_FRAME_OVERHEAD + sizeof(struct pt_regs);
#ifdef CONFIG_CHECK_STACK
	sp = __dump_trace(func, data, sp,
			  S390_lowcore.panic_stack + frame_size - PAGE_SIZE,
			  S390_lowcore.panic_stack + frame_size);
#endif
	sp = __dump_trace(func, data, sp,
			  S390_lowcore.async_stack + frame_size - ASYNC_SIZE,
			  S390_lowcore.async_stack + frame_size);
	task = task ?: current;
	__dump_trace(func, data, sp,
		     (unsigned long)task_stack_page(task),
		     (unsigned long)task_stack_page(task) + THREAD_SIZE);
}