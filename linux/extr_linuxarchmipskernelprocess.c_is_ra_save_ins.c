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
struct TYPE_2__ {scalar_t__ opcode; int rs; int rt; int simmediate; } ;
union mips_instruction {TYPE_1__ i_format; } ;
typedef  int /*<<< orphan*/  ulong ;

/* Variables and functions */
 scalar_t__ sd_op ; 
 scalar_t__ sw_op ; 

__attribute__((used)) static inline int is_ra_save_ins(union mips_instruction *ip, int *poff)
{
#ifdef CONFIG_CPU_MICROMIPS
	/*
	 * swsp ra,offset
	 * swm16 reglist,offset(sp)
	 * swm32 reglist,offset(sp)
	 * sw32 ra,offset(sp)
	 * jradiussp - NOT SUPPORTED
	 *
	 * microMIPS is way more fun...
	 */
	if (mm_insn_16bit(ip->word >> 16)) {
		switch (ip->mm16_r5_format.opcode) {
		case mm_swsp16_op:
			if (ip->mm16_r5_format.rt != 31)
				return 0;

			*poff = ip->mm16_r5_format.imm;
			*poff = (*poff << 2) / sizeof(ulong);
			return 1;

		case mm_pool16c_op:
			switch (ip->mm16_m_format.func) {
			case mm_swm16_op:
				*poff = ip->mm16_m_format.imm;
				*poff += 1 + ip->mm16_m_format.rlist;
				*poff = (*poff << 2) / sizeof(ulong);
				return 1;

			default:
				return 0;
			}

		default:
			return 0;
		}
	}

	switch (ip->i_format.opcode) {
	case mm_sw32_op:
		if (ip->i_format.rs != 29)
			return 0;
		if (ip->i_format.rt != 31)
			return 0;

		*poff = ip->i_format.simmediate / sizeof(ulong);
		return 1;

	case mm_pool32b_op:
		switch (ip->mm_m_format.func) {
		case mm_swm32_func:
			if (ip->mm_m_format.rd < 0x10)
				return 0;
			if (ip->mm_m_format.base != 29)
				return 0;

			*poff = ip->mm_m_format.simmediate;
			*poff += (ip->mm_m_format.rd & 0xf) * sizeof(u32);
			*poff /= sizeof(ulong);
			return 1;
		default:
			return 0;
		}

	default:
		return 0;
	}
#else
	/* sw / sd $ra, offset($sp) */
	if ((ip->i_format.opcode == sw_op || ip->i_format.opcode == sd_op) &&
		ip->i_format.rs == 29 && ip->i_format.rt == 31) {
		*poff = ip->i_format.simmediate / sizeof(ulong);
		return 1;
	}

	return 0;
#endif
}