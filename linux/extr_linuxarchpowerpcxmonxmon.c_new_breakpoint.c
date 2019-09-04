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
struct bpt {unsigned long address; int /*<<< orphan*/ * instr; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 size_t NBPTS ; 
 struct bpt* at_breakpoint (unsigned long) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpinstr ; 
 struct bpt* bpts ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  store_inst (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bpt *new_breakpoint(unsigned long a)
{
	struct bpt *bp;

	a &= ~3UL;
	bp = at_breakpoint(a);
	if (bp)
		return bp;

	for (bp = bpts; bp < &bpts[NBPTS]; ++bp) {
		if (!bp->enabled && atomic_read(&bp->ref_count) == 0) {
			bp->address = a;
			bp->instr[1] = bpinstr;
			store_inst(&bp->instr[1]);
			return bp;
		}
	}

	printf("Sorry, no free breakpoints.  Please clear one first.\n");
	return NULL;
}