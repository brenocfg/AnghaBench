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
struct stackframe {int /*<<< orphan*/  pc; } ;
struct perf_callchain_entry_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int callchain_trace(struct stackframe *frame, void *data)
{
	struct perf_callchain_entry_ctx *entry = data;

	perf_callchain_store(entry, frame->pc);
	return 0;
}