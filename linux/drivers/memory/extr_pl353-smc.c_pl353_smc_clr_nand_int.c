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
 int /*<<< orphan*/  PL353_SMC_CFG_CLR_INT_CLR_1 ; 
 scalar_t__ PL353_SMC_CFG_CLR_OFFS ; 
 scalar_t__ pl353_smc_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void pl353_smc_clr_nand_int(void)
{
	writel(PL353_SMC_CFG_CLR_INT_CLR_1,
	       pl353_smc_base + PL353_SMC_CFG_CLR_OFFS);
}