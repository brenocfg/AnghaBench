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

/* Variables and functions */
 int UM_FIXUP ; 
 int UM_SIGNAL ; 
 scalar_t__ cpu_is_v6_unaligned () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int safe_usermode(int new_usermode, bool warn)
{
	/*
	 * ARMv6 and later CPUs can perform unaligned accesses for
	 * most single load and store instructions up to word size.
	 * LDM, STM, LDRD and STRD still need to be handled.
	 *
	 * Ignoring the alignment fault is not an option on these
	 * CPUs since we spin re-faulting the instruction without
	 * making any progress.
	 */
	if (cpu_is_v6_unaligned() && !(new_usermode & (UM_FIXUP | UM_SIGNAL))) {
		new_usermode |= UM_FIXUP;

		if (warn)
			pr_warn("alignment: ignoring faults is unsafe on this CPU.  Defaulting to fixup mode.\n");
	}

	return new_usermode;
}