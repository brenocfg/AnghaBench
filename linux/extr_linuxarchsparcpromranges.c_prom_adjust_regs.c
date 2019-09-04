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
struct linux_prom_registers {scalar_t__ which_io; int /*<<< orphan*/  phys_addr; } ;
struct linux_prom_ranges {scalar_t__ ot_child_space; scalar_t__ ot_parent_space; scalar_t__ ot_parent_base; scalar_t__ ot_child_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  prom_printf (char*) ; 

__attribute__((used)) static void prom_adjust_regs(struct linux_prom_registers *regp, int nregs,
			     struct linux_prom_ranges *rangep, int nranges)
{
	int regc, rngc;

	for (regc = 0; regc < nregs; regc++) {
		for (rngc = 0; rngc < nranges; rngc++)
			if (regp[regc].which_io == rangep[rngc].ot_child_space)
				break; /* Fount it */
		if (rngc == nranges) /* oops */
			prom_printf("adjust_regs: Could not find range with matching bus type...\n");
		regp[regc].which_io = rangep[rngc].ot_parent_space;
		regp[regc].phys_addr -= rangep[rngc].ot_child_base;
		regp[regc].phys_addr += rangep[rngc].ot_parent_base;
	}
}