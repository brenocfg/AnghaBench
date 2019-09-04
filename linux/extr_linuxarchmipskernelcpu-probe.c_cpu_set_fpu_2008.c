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
struct cpuinfo_mips {int isa_level; unsigned long fpu_msk31; unsigned long fpu_csr31; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP1_REVISION ; 
 int /*<<< orphan*/  CP1_STATUS ; 
 int /*<<< orphan*/  FPU_AS_IS ; 
 unsigned long FPU_CSR_ABS2008 ; 
 unsigned long FPU_CSR_NAN2008 ; 
 int MIPS_CPU_ISA_M32R1 ; 
 int MIPS_CPU_ISA_M32R2 ; 
 int MIPS_CPU_ISA_M32R6 ; 
 int MIPS_CPU_ISA_M64R1 ; 
 int MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_ISA_M64R6 ; 
 int /*<<< orphan*/  MIPS_CPU_NAN_2008 ; 
 int /*<<< orphan*/  MIPS_CPU_NAN_LEGACY ; 
 unsigned long MIPS_FPIR_HAS2008 ; 
 int /*<<< orphan*/  __enable_fpu (int /*<<< orphan*/ ) ; 
 unsigned long read_32bit_cp1_register (int /*<<< orphan*/ ) ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_32bit_cp1_register (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static void cpu_set_fpu_2008(struct cpuinfo_mips *c)
{
	if (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) {
		unsigned long sr, fir, fcsr, fcsr0, fcsr1;

		sr = read_c0_status();
		__enable_fpu(FPU_AS_IS);

		fir = read_32bit_cp1_register(CP1_REVISION);
		if (fir & MIPS_FPIR_HAS2008) {
			fcsr = read_32bit_cp1_register(CP1_STATUS);

			fcsr0 = fcsr & ~(FPU_CSR_ABS2008 | FPU_CSR_NAN2008);
			write_32bit_cp1_register(CP1_STATUS, fcsr0);
			fcsr0 = read_32bit_cp1_register(CP1_STATUS);

			fcsr1 = fcsr | FPU_CSR_ABS2008 | FPU_CSR_NAN2008;
			write_32bit_cp1_register(CP1_STATUS, fcsr1);
			fcsr1 = read_32bit_cp1_register(CP1_STATUS);

			write_32bit_cp1_register(CP1_STATUS, fcsr);

			if (!(fcsr0 & FPU_CSR_NAN2008))
				c->options |= MIPS_CPU_NAN_LEGACY;
			if (fcsr1 & FPU_CSR_NAN2008)
				c->options |= MIPS_CPU_NAN_2008;

			if ((fcsr0 ^ fcsr1) & FPU_CSR_ABS2008)
				c->fpu_msk31 &= ~FPU_CSR_ABS2008;
			else
				c->fpu_csr31 |= fcsr & FPU_CSR_ABS2008;

			if ((fcsr0 ^ fcsr1) & FPU_CSR_NAN2008)
				c->fpu_msk31 &= ~FPU_CSR_NAN2008;
			else
				c->fpu_csr31 |= fcsr & FPU_CSR_NAN2008;
		} else {
			c->options |= MIPS_CPU_NAN_LEGACY;
		}

		write_c0_status(sr);
	} else {
		c->options |= MIPS_CPU_NAN_LEGACY;
	}
}