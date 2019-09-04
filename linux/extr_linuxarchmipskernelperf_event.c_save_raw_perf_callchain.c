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
struct perf_callchain_entry_ctx {scalar_t__ nr; scalar_t__ max_stack; } ;

/* Variables and functions */
 scalar_t__ __kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  kstack_end (unsigned long*) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry_ctx*,unsigned long) ; 

__attribute__((used)) static void save_raw_perf_callchain(struct perf_callchain_entry_ctx *entry,
				    unsigned long reg29)
{
	unsigned long *sp = (unsigned long *)reg29;
	unsigned long addr;

	while (!kstack_end(sp)) {
		addr = *sp++;
		if (__kernel_text_address(addr)) {
			perf_callchain_store(entry, addr);
			if (entry->nr >= entry->max_stack)
				break;
		}
	}
}