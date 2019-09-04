#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
typedef  TYPE_1__ Elf32_Rel ;
typedef  scalar_t__ Elf32_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_ARM_CALL 132 
#define  R_ARM_JUMP24 131 
#define  R_ARM_PC24 130 
#define  R_ARM_THM_CALL 129 
#define  R_ARM_THM_JUMP24 128 
 int __mem_to_opcode_arm (int /*<<< orphan*/ ) ; 
 int __mem_to_opcode_thumb16 (int) ; 

__attribute__((used)) static bool is_zero_addend_relocation(Elf32_Addr base, const Elf32_Rel *rel)
{
	u32 *tval = (u32 *)(base + rel->r_offset);

	/*
	 * Do a bitwise compare on the raw addend rather than fully decoding
	 * the offset and doing an arithmetic comparison.
	 * Note that a zero-addend jump/call relocation is encoded taking the
	 * PC bias into account, i.e., -8 for ARM and -4 for Thumb2.
	 */
	switch (ELF32_R_TYPE(rel->r_info)) {
		u16 upper, lower;

	case R_ARM_THM_CALL:
	case R_ARM_THM_JUMP24:
		upper = __mem_to_opcode_thumb16(((u16 *)tval)[0]);
		lower = __mem_to_opcode_thumb16(((u16 *)tval)[1]);

		return (upper & 0x7ff) == 0x7ff && (lower & 0x2fff) == 0x2ffe;

	case R_ARM_CALL:
	case R_ARM_PC24:
	case R_ARM_JUMP24:
		return (__mem_to_opcode_arm(*tval) & 0xffffff) == 0xfffffe;
	}
	BUG();
}