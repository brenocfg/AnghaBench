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
struct cpuinfo_mips {int isa_level; int options; int fpu_id; } ;

/* Variables and functions */
 int MIPS_CPU_ISA_M32R1 ; 
 int MIPS_CPU_ISA_M32R2 ; 
 int MIPS_CPU_ISA_M32R6 ; 
 int MIPS_CPU_ISA_M64R1 ; 
 int MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_ISA_M64R6 ; 
 int MIPS_CPU_NAN_2008 ; 
 int MIPS_FPIR_D ; 
 int MIPS_FPIR_F64 ; 
 int MIPS_FPIR_HAS2008 ; 
 int MIPS_FPIR_L ; 
 int MIPS_FPIR_S ; 
 int MIPS_FPIR_W ; 

__attribute__((used)) static void cpu_set_nofpu_id(struct cpuinfo_mips *c)
{
	u32 value;

	value = 0;
	if (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6))
		value |= MIPS_FPIR_D | MIPS_FPIR_S;
	if (c->isa_level & (MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6))
		value |= MIPS_FPIR_F64 | MIPS_FPIR_L | MIPS_FPIR_W;
	if (c->options & MIPS_CPU_NAN_2008)
		value |= MIPS_FPIR_HAS2008;
	c->fpu_id = value;
}