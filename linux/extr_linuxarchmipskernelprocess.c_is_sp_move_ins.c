#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rs; int rt; scalar_t__ opcode; int simmediate; } ;
union mips_instruction {TYPE_1__ i_format; } ;

/* Variables and functions */
 scalar_t__ addiu_op ; 
 scalar_t__ daddiu_op ; 

__attribute__((used)) static inline int is_sp_move_ins(union mips_instruction *ip, int *frame_size)
{
#ifdef CONFIG_CPU_MICROMIPS
	unsigned short tmp;

	/*
	 * addiusp -imm
	 * addius5 sp,-imm
	 * addiu32 sp,sp,-imm
	 * jradiussp - NOT SUPPORTED
	 *
	 * microMIPS is not more fun...
	 */
	if (mm_insn_16bit(ip->word >> 16)) {
		if (ip->mm16_r3_format.opcode == mm_pool16d_op &&
		    ip->mm16_r3_format.simmediate & mm_addiusp_func) {
			tmp = ip->mm_b0_format.simmediate >> 1;
			tmp = ((tmp & 0x1ff) ^ 0x100) - 0x100;
			if ((tmp + 2) < 4) /* 0x0,0x1,0x1fe,0x1ff are special */
				tmp ^= 0x100;
			*frame_size = -(signed short)(tmp << 2);
			return 1;
		}
		if (ip->mm16_r5_format.opcode == mm_pool16d_op &&
		    ip->mm16_r5_format.rt == 29) {
			tmp = ip->mm16_r5_format.imm >> 1;
			*frame_size = -(signed short)(tmp & 0xf);
			return 1;
		}
		return 0;
	}

	if (ip->mm_i_format.opcode == mm_addiu32_op &&
	    ip->mm_i_format.rt == 29 && ip->mm_i_format.rs == 29) {
		*frame_size = -ip->i_format.simmediate;
		return 1;
	}
#else
	/* addiu/daddiu sp,sp,-imm */
	if (ip->i_format.rs != 29 || ip->i_format.rt != 29)
		return 0;

	if (ip->i_format.opcode == addiu_op ||
	    ip->i_format.opcode == daddiu_op) {
		*frame_size = -ip->i_format.simmediate;
		return 1;
	}
#endif
	return 0;
}