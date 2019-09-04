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
struct cpuinfo_mips {int fpu_id; int isa_level; int /*<<< orphan*/  options; int /*<<< orphan*/  ases; int /*<<< orphan*/  fpu_msk31; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_ASE_MIPS3D ; 
 int /*<<< orphan*/  MIPS_CPU_FRE ; 
 int MIPS_CPU_ISA_M32R1 ; 
 int MIPS_CPU_ISA_M32R2 ; 
 int MIPS_CPU_ISA_M32R6 ; 
 int MIPS_CPU_ISA_M64R1 ; 
 int MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_ISA_M64R6 ; 
 int /*<<< orphan*/  MIPS_CPU_UFR ; 
 int MIPS_FPIR_3D ; 
 int MIPS_FPIR_FREP ; 
 int MIPS_FPIR_UFRP ; 
 int cpu_get_fpu_id () ; 
 int /*<<< orphan*/  cpu_set_fpu_2008 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_set_fpu_fcsr_mask (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_set_nan_2008 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  mips_nofpu_msk31 ; 

__attribute__((used)) static void cpu_set_fpu_opts(struct cpuinfo_mips *c)
{
	c->fpu_id = cpu_get_fpu_id();
	mips_nofpu_msk31 = c->fpu_msk31;

	if (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) {
		if (c->fpu_id & MIPS_FPIR_3D)
			c->ases |= MIPS_ASE_MIPS3D;
		if (c->fpu_id & MIPS_FPIR_UFRP)
			c->options |= MIPS_CPU_UFR;
		if (c->fpu_id & MIPS_FPIR_FREP)
			c->options |= MIPS_CPU_FRE;
	}

	cpu_set_fpu_fcsr_mask(c);
	cpu_set_fpu_2008(c);
	cpu_set_nan_2008(c);
}