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
 int PL353_SMC_ECC_STATUS_BUSY ; 
 scalar_t__ PL353_SMC_ECC_STATUS_OFFS ; 
 scalar_t__ pl353_smc_base ; 
 int readl (scalar_t__) ; 

bool pl353_smc_ecc_is_busy(void)
{
	return ((readl(pl353_smc_base + PL353_SMC_ECC_STATUS_OFFS) &
		  PL353_SMC_ECC_STATUS_BUSY) == PL353_SMC_ECC_STATUS_BUSY);
}