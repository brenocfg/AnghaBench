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
struct seq_file {int dummy; } ;
struct pg_state {int /*<<< orphan*/  marker; int /*<<< orphan*/  start_address; struct seq_file* seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_OFFSET ; 
 int /*<<< orphan*/  address_markers ; 
 int /*<<< orphan*/  walk_linearmapping (struct pg_state*) ; 
 int /*<<< orphan*/  walk_pagetables (struct pg_state*) ; 
 int /*<<< orphan*/  walk_vmemmap (struct pg_state*) ; 

__attribute__((used)) static int ptdump_show(struct seq_file *m, void *v)
{
	struct pg_state st = {
		.seq = m,
		.start_address = PAGE_OFFSET,
		.marker = address_markers,
	};
	/*
	 * Traverse the 0xc, 0xd and 0xf areas of the kernel virtual memory and
	 * dump pages that are in the hash pagetable.
	 */
	walk_linearmapping(&st);
	walk_pagetables(&st);
	walk_vmemmap(&st);
	return 0;
}