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

__attribute__((used)) static inline int check_io_access(struct pt_regs *regs)
{
#ifdef CONFIG_PPC32
	unsigned long msr = regs->msr;
	const struct exception_table_entry *entry;
	unsigned int *nip = (unsigned int *)regs->nip;

	if (((msr & 0xffff0000) == 0 || (msr & (0x80000 | 0x40000)))
	    && (entry = search_exception_tables(regs->nip)) != NULL) {
		/*
		 * Check that it's a sync instruction, or somewhere
		 * in the twi; isync; nop sequence that inb/inw/inl uses.
		 * As the address is in the exception table
		 * we should be able to read the instr there.
		 * For the debug message, we look at the preceding
		 * load or store.
		 */
		if (*nip == PPC_INST_NOP)
			nip -= 2;
		else if (*nip == PPC_INST_ISYNC)
			--nip;
		if (*nip == PPC_INST_SYNC || (*nip >> 26) == OP_TRAP) {
			unsigned int rb;

			--nip;
			rb = (*nip >> 11) & 0x1f;
			printk(KERN_DEBUG "%s bad port %lx at %p\n",
			       (*nip & 0x100)? "OUT to": "IN from",
			       regs->gpr[rb] - _IO_BASE, nip);
			regs->msr |= MSR_RI;
			regs->nip = extable_fixup(entry);
			return 1;
		}
	}
#endif /* CONFIG_PPC32 */
	return 0;
}