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
struct pt_regs {unsigned long ipc; int pipsw; int ipsw; scalar_t__ pipc; } ;

/* Variables and functions */
 unsigned long ETYPE_ALIGNMENT_CHECK ; 
 unsigned long ETYPE_RESERVED_INSTRUCTION ; 
 unsigned long ETYPE_TRAP ; 
 unsigned long ITYPE_mskETYPE ; 
 unsigned long ITYPE_mskINST ; 
 unsigned long ITYPE_offSWID ; 
 int PSW_mskDEX ; 
 unsigned int SWID_RAISE_INTERRUPT_LEVEL ; 
 int /*<<< orphan*/  do_debug_trap (unsigned long,unsigned long,unsigned long,struct pt_regs*) ; 
 int /*<<< orphan*/  do_page_fault (unsigned long,unsigned long,unsigned long,struct pt_regs*) ; 
 int /*<<< orphan*/  do_revinsn (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 
 int /*<<< orphan*/  unhandled_exceptions (unsigned long,unsigned long,unsigned long,struct pt_regs*) ; 

void do_dispatch_general(unsigned long entry, unsigned long addr,
			 unsigned long itype, struct pt_regs *regs,
			 unsigned long oipc)
{
	unsigned int swid = itype >> ITYPE_offSWID;
	unsigned long type = itype & (ITYPE_mskINST | ITYPE_mskETYPE);
	if (type == ETYPE_ALIGNMENT_CHECK) {
#ifdef CONFIG_ALIGNMENT_TRAP
		/* Alignment check */
		if (user_mode(regs) && unalign_access_mode) {
			int ret;
			ret = do_unaligned_access(addr, regs);

			if (ret == 0)
				return;

			if (ret == -EFAULT)
				pr_emerg
				    ("Unhandled unaligned access exception\n");
		}
#endif
		do_page_fault(entry, addr, type, regs);
	} else if (type == ETYPE_RESERVED_INSTRUCTION) {
		/* Reserved instruction */
		do_revinsn(regs);
	} else if (type == ETYPE_TRAP && swid == SWID_RAISE_INTERRUPT_LEVEL) {
		/* trap, used on v3 EDM target debugging workaround */
		/*
		 * DIPC(OIPC) is passed as parameter before
		 * interrupt is enabled, so the DIPC will not be corrupted
		 * even though interrupts are coming in
		 */
		/*
		 * 1. update ipc
		 * 2. update pt_regs ipc with oipc
		 * 3. update pt_regs ipsw (clear DEX)
		 */
		__asm__ volatile ("mtsr %0, $IPC\n\t"::"r" (oipc));
		regs->ipc = oipc;
		if (regs->pipsw & PSW_mskDEX) {
			pr_emerg
			    ("Nested Debug exception is possibly happened\n");
			pr_emerg("ipc:%08x pipc:%08x\n",
				 (unsigned int)regs->ipc,
				 (unsigned int)regs->pipc);
		}
		do_debug_trap(entry, addr, itype, regs);
		regs->ipsw &= ~PSW_mskDEX;
	} else
		unhandled_exceptions(entry, addr, type, regs);
}