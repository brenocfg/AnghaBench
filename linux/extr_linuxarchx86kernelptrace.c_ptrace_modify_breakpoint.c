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
struct perf_event_attr {int dummy; } ;
struct perf_event {struct perf_event_attr attr; } ;

/* Variables and functions */
 int modify_user_hw_breakpoint (struct perf_event*,struct perf_event_attr*) ; 
 int ptrace_fill_bp_fields (struct perf_event_attr*,int,int,int) ; 

__attribute__((used)) static int ptrace_modify_breakpoint(struct perf_event *bp, int len, int type,
					int disabled)
{
	struct perf_event_attr attr = bp->attr;
	int err;

	err = ptrace_fill_bp_fields(&attr, len, type, disabled);
	if (err)
		return err;

	return modify_user_hw_breakpoint(bp, &attr);
}