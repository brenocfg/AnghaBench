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
 scalar_t__ PL353_SMC_MEMC_STATUS_OFFS ; 
 int PL353_SMC_MEMC_STATUS_RAW_INT_1_SHIFT ; 
 scalar_t__ pl353_smc_base ; 
 int readl (scalar_t__) ; 

int pl353_smc_get_nand_int_status_raw(void)
{
	u32 reg;

	reg = readl(pl353_smc_base + PL353_SMC_MEMC_STATUS_OFFS);
	reg >>= PL353_SMC_MEMC_STATUS_RAW_INT_1_SHIFT;
	reg &= 1;

	return reg;
}