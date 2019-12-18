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

/* Variables and functions */
 int EINVAL ; 
 unsigned int PL353_SMC_DC_UPT_NAND_REGS ; 
 scalar_t__ PL353_SMC_DIRECT_CMD_OFFS ; 
 unsigned int PL353_SMC_MEM_WIDTH_16 ; 
 unsigned int PL353_SMC_MEM_WIDTH_8 ; 
 scalar_t__ PL353_SMC_SET_OPMODE_OFFS ; 
 scalar_t__ pl353_smc_base ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

int pl353_smc_set_buswidth(unsigned int bw)
{
	if (bw != PL353_SMC_MEM_WIDTH_8  && bw != PL353_SMC_MEM_WIDTH_16)
		return -EINVAL;

	writel(bw, pl353_smc_base + PL353_SMC_SET_OPMODE_OFFS);
	writel(PL353_SMC_DC_UPT_NAND_REGS, pl353_smc_base +
	       PL353_SMC_DIRECT_CMD_OFFS);

	return 0;
}