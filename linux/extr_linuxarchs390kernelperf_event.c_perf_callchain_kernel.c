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
struct pt_regs {int /*<<< orphan*/ * gprs; } ;
struct perf_callchain_entry_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_callchain_kernel ; 
 int /*<<< orphan*/  dump_trace (int /*<<< orphan*/ ,struct perf_callchain_entry_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void perf_callchain_kernel(struct perf_callchain_entry_ctx *entry,
			   struct pt_regs *regs)
{
	if (user_mode(regs))
		return;
	dump_trace(__perf_callchain_kernel, entry, NULL, regs->gprs[15]);
}