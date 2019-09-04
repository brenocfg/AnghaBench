#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ opcode; scalar_t__ func; } ;
struct TYPE_3__ {scalar_t__ opcode; } ;
union mips_instruction {TYPE_2__ r_format; TYPE_1__ j_format; } ;

/* Variables and functions */
 scalar_t__ j_op ; 
 scalar_t__ jal_op ; 
 scalar_t__ jalr_op ; 
 scalar_t__ jr_op ; 
 scalar_t__ spec_op ; 

__attribute__((used)) static inline int is_jump_ins(union mips_instruction *ip)
{
#ifdef CONFIG_CPU_MICROMIPS
	/*
	 * jr16,jrc,jalr16,jalr16
	 * jal
	 * jalr/jr,jalr.hb/jr.hb,jalrs,jalrs.hb
	 * jraddiusp - NOT SUPPORTED
	 *
	 * microMIPS is kind of more fun...
	 */
	if (mm_insn_16bit(ip->word >> 16)) {
		if ((ip->mm16_r5_format.opcode == mm_pool16c_op &&
		    (ip->mm16_r5_format.rt & mm_jr16_op) == mm_jr16_op))
			return 1;
		return 0;
	}

	if (ip->j_format.opcode == mm_j32_op)
		return 1;
	if (ip->j_format.opcode == mm_jal32_op)
		return 1;
	if (ip->r_format.opcode != mm_pool32a_op ||
			ip->r_format.func != mm_pool32axf_op)
		return 0;
	return ((ip->u_format.uimmediate >> 6) & mm_jalr_op) == mm_jalr_op;
#else
	if (ip->j_format.opcode == j_op)
		return 1;
	if (ip->j_format.opcode == jal_op)
		return 1;
	if (ip->r_format.opcode != spec_op)
		return 0;
	return ip->r_format.func == jalr_op || ip->r_format.func == jr_op;
#endif
}