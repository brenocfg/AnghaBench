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
struct task_struct {int dummy; } ;
struct perf_event_attr {unsigned long bp_addr; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 struct perf_event* ERR_PTR (int) ; 
 int /*<<< orphan*/  ptrace_breakpoint_init (struct perf_event_attr*) ; 
 int ptrace_fill_bp_fields (struct perf_event_attr*,int,int,int) ; 
 int /*<<< orphan*/  ptrace_triggered ; 
 struct perf_event* register_user_hw_breakpoint (struct perf_event_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct task_struct*) ; 

__attribute__((used)) static struct perf_event *
ptrace_register_breakpoint(struct task_struct *tsk, int len, int type,
				unsigned long addr, bool disabled)
{
	struct perf_event_attr attr;
	int err;

	ptrace_breakpoint_init(&attr);
	attr.bp_addr = addr;

	err = ptrace_fill_bp_fields(&attr, len, type, disabled);
	if (err)
		return ERR_PTR(err);

	return register_user_hw_breakpoint(&attr, ptrace_triggered,
						 NULL, tsk);
}