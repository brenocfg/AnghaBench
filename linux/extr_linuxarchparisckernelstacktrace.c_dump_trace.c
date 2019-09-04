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
struct unwind_frame_info {scalar_t__ ip; } ;
struct task_struct {int dummy; } ;
struct stack_trace {scalar_t__ nr_entries; scalar_t__ max_entries; scalar_t__* entries; } ;

/* Variables and functions */
 scalar_t__ __kernel_text_address (scalar_t__) ; 
 int /*<<< orphan*/  unwind_frame_init_task (struct unwind_frame_info*,struct task_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ unwind_once (struct unwind_frame_info*) ; 

__attribute__((used)) static void dump_trace(struct task_struct *task, struct stack_trace *trace)
{
	struct unwind_frame_info info;

	unwind_frame_init_task(&info, task, NULL);

	/* unwind stack and save entries in stack_trace struct */
	trace->nr_entries = 0;
	while (trace->nr_entries < trace->max_entries) {
		if (unwind_once(&info) < 0 || info.ip == 0)
			break;

		if (__kernel_text_address(info.ip))
			trace->entries[trace->nr_entries++] = info.ip;
	}
}