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
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 unsigned int PPC_INST_ADDIS ; 
 unsigned int PPC_INST_ORI ; 
 unsigned int ___PPC_RA (int) ; 
 unsigned int ___PPC_RS (int) ; 
 unsigned int ___PPC_RT (int) ; 
 int /*<<< orphan*/  patch_instruction (int /*<<< orphan*/ *,unsigned int) ; 

void patch_imm32_load_insns(unsigned int val, kprobe_opcode_t *addr)
{
	/* addis r4,0,(insn)@h */
	patch_instruction(addr, PPC_INST_ADDIS | ___PPC_RT(4) |
			  ((val >> 16) & 0xffff));
	addr++;

	/* ori r4,r4,(insn)@l */
	patch_instruction(addr, PPC_INST_ORI | ___PPC_RA(4) |
			  ___PPC_RS(4) | (val & 0xffff));
}