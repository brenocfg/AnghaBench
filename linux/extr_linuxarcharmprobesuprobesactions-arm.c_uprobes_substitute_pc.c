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
typedef  int u32 ;
typedef  int probes_opcode_t ;

/* Variables and functions */
 int REG_TYPE_NONE ; 
 int __mem_to_opcode_arm (unsigned long) ; 
 unsigned long __opcode_to_mem_arm (int) ; 
 int fls (int) ; 

__attribute__((used)) static int uprobes_substitute_pc(unsigned long *pinsn, u32 oregs)
{
	probes_opcode_t insn = __mem_to_opcode_arm(*pinsn);
	probes_opcode_t temp;
	probes_opcode_t mask;
	int freereg;
	u32 free = 0xffff;
	u32 regs;

	for (regs = oregs; regs; regs >>= 4, insn >>= 4) {
		if ((regs & 0xf) == REG_TYPE_NONE)
			continue;

		free &= ~(1 << (insn & 0xf));
	}

	/* No PC, no problem */
	if (free & (1 << 15))
		return 15;

	if (!free)
		return -1;

	/*
	 * fls instead of ffs ensures that for "ldrd r0, r1, [pc]" we would
	 * pick LR instead of R1.
	 */
	freereg = free = fls(free) - 1;

	temp = __mem_to_opcode_arm(*pinsn);
	insn = temp;
	regs = oregs;
	mask = 0xf;

	for (; regs; regs >>= 4, mask <<= 4, free <<= 4, temp >>= 4) {
		if ((regs & 0xf) == REG_TYPE_NONE)
			continue;

		if ((temp & 0xf) != 15)
			continue;

		insn &= ~mask;
		insn |= free & mask;
	}

	*pinsn = __opcode_to_mem_arm(insn);
	return freereg;
}