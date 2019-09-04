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
typedef  int u8 ;
typedef  int u32 ;
typedef  int s16 ;

/* Variables and functions */
 int ARM_INST_LDST__IMM12 ; 
 int ARM_INST_LDST__U ; 

__attribute__((used)) static u32 arm_bpf_ldst_imm12(u32 op, u8 rt, u8 rn, s16 imm12)
{
	op |= rt << 12 | rn << 16;
	if (imm12 >= 0)
		op |= ARM_INST_LDST__U;
	else
		imm12 = -imm12;
	return op | (imm12 & ARM_INST_LDST__IMM12);
}