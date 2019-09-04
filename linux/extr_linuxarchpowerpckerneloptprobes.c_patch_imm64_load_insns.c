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
 unsigned long PPC_INST_ADDIS ; 
 unsigned long PPC_INST_ORI ; 
 unsigned long PPC_INST_ORIS ; 
 unsigned long PPC_INST_RLDICR ; 
 unsigned long __PPC_ME64 (int) ; 
 unsigned long __PPC_SH64 (int) ; 
 unsigned long ___PPC_RA (int) ; 
 unsigned long ___PPC_RS (int) ; 
 unsigned long ___PPC_RT (int) ; 
 int /*<<< orphan*/  patch_instruction (int /*<<< orphan*/ *,unsigned long) ; 

void patch_imm64_load_insns(unsigned long val, kprobe_opcode_t *addr)
{
	/* lis r3,(op)@highest */
	patch_instruction(addr, PPC_INST_ADDIS | ___PPC_RT(3) |
			  ((val >> 48) & 0xffff));
	addr++;

	/* ori r3,r3,(op)@higher */
	patch_instruction(addr, PPC_INST_ORI | ___PPC_RA(3) |
			  ___PPC_RS(3) | ((val >> 32) & 0xffff));
	addr++;

	/* rldicr r3,r3,32,31 */
	patch_instruction(addr, PPC_INST_RLDICR | ___PPC_RA(3) |
			  ___PPC_RS(3) | __PPC_SH64(32) | __PPC_ME64(31));
	addr++;

	/* oris r3,r3,(op)@h */
	patch_instruction(addr, PPC_INST_ORIS | ___PPC_RA(3) |
			  ___PPC_RS(3) | ((val >> 16) & 0xffff));
	addr++;

	/* ori r3,r3,(op)@l */
	patch_instruction(addr, PPC_INST_ORI | ___PPC_RA(3) |
			  ___PPC_RS(3) | (val & 0xffff));
}