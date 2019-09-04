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
union offset_union {unsigned long un; } ;
struct pt_regs {unsigned long* uregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDST_P_BIT (unsigned long) ; 
 int /*<<< orphan*/  LDST_U_BIT (unsigned long) ; 
 scalar_t__ LDST_W_BIT (unsigned long) ; 
 size_t RN_BITS (unsigned long) ; 

__attribute__((used)) static void
do_alignment_finish_ldst(unsigned long addr, unsigned long instr, struct pt_regs *regs, union offset_union offset)
{
	if (!LDST_U_BIT(instr))
		offset.un = -offset.un;

	if (!LDST_P_BIT(instr))
		addr += offset.un;

	if (!LDST_P_BIT(instr) || LDST_W_BIT(instr))
		regs->uregs[RN_BITS(instr)] = addr;
}