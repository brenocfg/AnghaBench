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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long ITYPE_mskETYPE ; 
 unsigned long ITYPE_mskINST ; 
 int /*<<< orphan*/  do_page_fault (unsigned long,unsigned long,unsigned long,struct pt_regs*) ; 
 int /*<<< orphan*/  unhandled_exceptions (unsigned long,unsigned long,unsigned long,struct pt_regs*) ; 

void do_dispatch_tlb_misc(unsigned long entry, unsigned long addr,
			  unsigned long type, struct pt_regs *regs)
{
	type = type & (ITYPE_mskINST | ITYPE_mskETYPE);
	if ((type & ITYPE_mskETYPE) < 5) {
		/* Permission exceptions */
		do_page_fault(entry, addr, type, regs);
	} else
		unhandled_exceptions(entry, addr, type, regs);
}