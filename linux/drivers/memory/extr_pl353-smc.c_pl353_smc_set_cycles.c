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

/* Variables and functions */
 int PL353_SMC_DC_UPT_NAND_REGS ; 
 scalar_t__ PL353_SMC_DIRECT_CMD_OFFS ; 
 scalar_t__ PL353_SMC_SET_CYCLES_OFFS ; 
 int PL353_SMC_SET_CYCLES_T0_MASK ; 
 int PL353_SMC_SET_CYCLES_T1_MASK ; 
 int PL353_SMC_SET_CYCLES_T1_SHIFT ; 
 int PL353_SMC_SET_CYCLES_T2_MASK ; 
 int PL353_SMC_SET_CYCLES_T2_SHIFT ; 
 int PL353_SMC_SET_CYCLES_T3_MASK ; 
 int PL353_SMC_SET_CYCLES_T3_SHIFT ; 
 int PL353_SMC_SET_CYCLES_T4_MASK ; 
 int PL353_SMC_SET_CYCLES_T4_SHIFT ; 
 int PL353_SMC_SET_CYCLES_T5_MASK ; 
 int PL353_SMC_SET_CYCLES_T5_SHIFT ; 
 int PL353_SMC_SET_CYCLES_T6_MASK ; 
 int PL353_SMC_SET_CYCLES_T6_SHIFT ; 
 scalar_t__ pl353_smc_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void pl353_smc_set_cycles(u32 timings[])
{
	/*
	 * Set write pulse timing. This one is easy to extract:
	 *
	 * NWE_PULSE = tWP
	 */
	timings[0] &= PL353_SMC_SET_CYCLES_T0_MASK;
	timings[1] = (timings[1] & PL353_SMC_SET_CYCLES_T1_MASK) <<
			PL353_SMC_SET_CYCLES_T1_SHIFT;
	timings[2] = (timings[2]  & PL353_SMC_SET_CYCLES_T2_MASK) <<
			PL353_SMC_SET_CYCLES_T2_SHIFT;
	timings[3] = (timings[3]  & PL353_SMC_SET_CYCLES_T3_MASK) <<
			PL353_SMC_SET_CYCLES_T3_SHIFT;
	timings[4] = (timings[4] & PL353_SMC_SET_CYCLES_T4_MASK) <<
			PL353_SMC_SET_CYCLES_T4_SHIFT;
	timings[5]  = (timings[5]  & PL353_SMC_SET_CYCLES_T5_MASK) <<
			PL353_SMC_SET_CYCLES_T5_SHIFT;
	timings[6]  = (timings[6]  & PL353_SMC_SET_CYCLES_T6_MASK) <<
			PL353_SMC_SET_CYCLES_T6_SHIFT;
	timings[0] |= timings[1] | timings[2] | timings[3] |
			timings[4] | timings[5] | timings[6];

	writel(timings[0], pl353_smc_base + PL353_SMC_SET_CYCLES_OFFS);
	writel(PL353_SMC_DC_UPT_NAND_REGS, pl353_smc_base +
	       PL353_SMC_DIRECT_CMD_OFFS);
}