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
struct TYPE_2__ {struct pt_regs* segv_regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct stacktrace_ops {int /*<<< orphan*/  (* address ) (void*,unsigned long,int) ;} ;
struct stack_frame {struct stack_frame* next_frame; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int THREAD_SIZE ; 
 scalar_t__ __kernel_text_address (unsigned long) ; 
 unsigned long get_frame_pointer (struct task_struct*,struct pt_regs*) ; 
 unsigned long* get_stack_pointer (struct task_struct*,struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (void*,unsigned long,int) ; 

void dump_trace(struct task_struct *tsk,
		const struct stacktrace_ops *ops,
		void *data)
{
	int reliable = 0;
	unsigned long *sp, bp, addr;
	struct pt_regs *segv_regs = tsk->thread.segv_regs;
	struct stack_frame *frame;

	bp = get_frame_pointer(tsk, segv_regs);
	sp = get_stack_pointer(tsk, segv_regs);

	frame = (struct stack_frame *)bp;
	while (((long) sp & (THREAD_SIZE-1)) != 0) {
		addr = *sp;
		if (__kernel_text_address(addr)) {
			reliable = 0;
			if ((unsigned long) sp == bp + sizeof(long)) {
				frame = frame ? frame->next_frame : NULL;
				bp = (unsigned long)frame;
				reliable = 1;
			}
			ops->address(data, addr, reliable);
		}
		sp++;
	}
}