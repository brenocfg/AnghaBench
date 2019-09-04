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
struct cpuinfo_mips {unsigned long fpu_csr31; unsigned long fpu_msk31; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP1_STATUS ; 
 int /*<<< orphan*/  FPU_AS_IS ; 
 unsigned long FPU_CSR_ALL_E ; 
 unsigned long FPU_CSR_ALL_S ; 
 unsigned long FPU_CSR_ALL_X ; 
 unsigned long FPU_CSR_RM ; 
 int /*<<< orphan*/  __enable_fpu (int /*<<< orphan*/ ) ; 
 unsigned long read_32bit_cp1_register (int /*<<< orphan*/ ) ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_32bit_cp1_register (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static inline void cpu_set_fpu_fcsr_mask(struct cpuinfo_mips *c)
{
	unsigned long sr, mask, fcsr, fcsr0, fcsr1;

	fcsr = c->fpu_csr31;
	mask = FPU_CSR_ALL_X | FPU_CSR_ALL_E | FPU_CSR_ALL_S | FPU_CSR_RM;

	sr = read_c0_status();
	__enable_fpu(FPU_AS_IS);

	fcsr0 = fcsr & mask;
	write_32bit_cp1_register(CP1_STATUS, fcsr0);
	fcsr0 = read_32bit_cp1_register(CP1_STATUS);

	fcsr1 = fcsr | ~mask;
	write_32bit_cp1_register(CP1_STATUS, fcsr1);
	fcsr1 = read_32bit_cp1_register(CP1_STATUS);

	write_32bit_cp1_register(CP1_STATUS, fcsr);

	write_c0_status(sr);

	c->fpu_msk31 = ~(fcsr0 ^ fcsr1) & ~mask;
}