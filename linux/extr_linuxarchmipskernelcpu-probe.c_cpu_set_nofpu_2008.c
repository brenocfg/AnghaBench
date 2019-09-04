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
struct cpuinfo_mips {int options; int fpu_csr31; int fpu_msk31; int isa_level; } ;

/* Variables and functions */
 int FPU_CSR_ABS2008 ; 
 int FPU_CSR_NAN2008 ; 
#define  LEGACY 131 
 int MIPS_CPU_ISA_M32R1 ; 
 int MIPS_CPU_ISA_M32R2 ; 
 int MIPS_CPU_ISA_M32R6 ; 
 int MIPS_CPU_ISA_M64R1 ; 
 int MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_ISA_M64R6 ; 
 int MIPS_CPU_NAN_2008 ; 
 int MIPS_CPU_NAN_LEGACY ; 
#define  RELAXED 130 
#define  STD2008 129 
#define  STRICT 128 
 int ieee754 ; 

__attribute__((used)) static void cpu_set_nofpu_2008(struct cpuinfo_mips *c)
{
	c->options &= ~(MIPS_CPU_NAN_2008 | MIPS_CPU_NAN_LEGACY);
	c->fpu_csr31 &= ~(FPU_CSR_ABS2008 | FPU_CSR_NAN2008);
	c->fpu_msk31 &= ~(FPU_CSR_ABS2008 | FPU_CSR_NAN2008);

	switch (ieee754) {
	case STRICT:
		if (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
				    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
				    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) {
			c->options |= MIPS_CPU_NAN_2008 | MIPS_CPU_NAN_LEGACY;
		} else {
			c->options |= MIPS_CPU_NAN_LEGACY;
			c->fpu_msk31 |= FPU_CSR_ABS2008 | FPU_CSR_NAN2008;
		}
		break;
	case LEGACY:
		c->options |= MIPS_CPU_NAN_LEGACY;
		c->fpu_msk31 |= FPU_CSR_ABS2008 | FPU_CSR_NAN2008;
		break;
	case STD2008:
		c->options |= MIPS_CPU_NAN_2008;
		c->fpu_csr31 |= FPU_CSR_ABS2008 | FPU_CSR_NAN2008;
		c->fpu_msk31 |= FPU_CSR_ABS2008 | FPU_CSR_NAN2008;
		break;
	case RELAXED:
		c->options |= MIPS_CPU_NAN_2008 | MIPS_CPU_NAN_LEGACY;
		break;
	}
}