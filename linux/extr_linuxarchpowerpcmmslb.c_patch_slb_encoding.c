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
 int /*<<< orphan*/  patch_instruction (unsigned int*,unsigned int) ; 

__attribute__((used)) static inline void patch_slb_encoding(unsigned int *insn_addr,
				      unsigned int immed)
{

	/*
	 * This function patches either an li or a cmpldi instruction with
	 * a new immediate value. This relies on the fact that both li
	 * (which is actually addi) and cmpldi both take a 16-bit immediate
	 * value, and it is situated in the same location in the instruction,
	 * ie. bits 16-31 (Big endian bit order) or the lower 16 bits.
	 * The signedness of the immediate operand differs between the two
	 * instructions however this code is only ever patching a small value,
	 * much less than 1 << 15, so we can get away with it.
	 * To patch the value we read the existing instruction, clear the
	 * immediate value, and or in our new value, then write the instruction
	 * back.
	 */
	unsigned int insn = (*insn_addr & 0xffff0000) | immed;
	patch_instruction(insn_addr, insn);
}