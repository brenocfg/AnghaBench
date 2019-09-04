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
struct pt_regs {int /*<<< orphan*/ * uregs; } ;

/* Variables and functions */
 scalar_t__ LDST_L_BIT (unsigned long) ; 
 int /*<<< orphan*/  LDST_P_BIT (unsigned long) ; 
 scalar_t__ LDST_W_BIT (unsigned long) ; 
 unsigned int RD_BITS (unsigned long) ; 
 int TYPE_FAULT ; 
 int TYPE_LDST ; 
 int /*<<< orphan*/  get32_unaligned_check (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  get32t_unaligned_check (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  put32_unaligned_check (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  put32t_unaligned_check (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int
do_alignment_ldrstr(unsigned long addr, unsigned long instr,
		    struct pt_regs *regs)
{
	unsigned int rd = RD_BITS(instr);

	if (!LDST_P_BIT(instr) && LDST_W_BIT(instr))
		goto trans;

	if (LDST_L_BIT(instr))
		get32_unaligned_check(regs->uregs[rd], addr);
	else
		put32_unaligned_check(regs->uregs[rd], addr);
	return TYPE_LDST;

trans:
	if (LDST_L_BIT(instr))
		get32t_unaligned_check(regs->uregs[rd], addr);
	else
		put32t_unaligned_check(regs->uregs[rd], addr);
	return TYPE_LDST;

fault:
	return TYPE_FAULT;
}