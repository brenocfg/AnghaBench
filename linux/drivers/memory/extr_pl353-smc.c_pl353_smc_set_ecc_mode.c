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
typedef  enum pl353_smc_ecc_mode { ____Placeholder_pl353_smc_ecc_mode } pl353_smc_ecc_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  PL353_SMC_ECCMODE_APB 130 
#define  PL353_SMC_ECCMODE_BYPASS 129 
#define  PL353_SMC_ECCMODE_MEM 128 
 int PL353_SMC_ECC_MEMCFG_MODE_MASK ; 
 int PL353_SMC_ECC_MEMCFG_MODE_SHIFT ; 
 scalar_t__ PL353_SMC_ECC_MEMCFG_OFFS ; 
 scalar_t__ pl353_smc_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int pl353_smc_set_ecc_mode(enum pl353_smc_ecc_mode mode)
{
	u32 reg;
	int ret = 0;

	switch (mode) {
	case PL353_SMC_ECCMODE_BYPASS:
	case PL353_SMC_ECCMODE_APB:
	case PL353_SMC_ECCMODE_MEM:

		reg = readl(pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);
		reg &= ~PL353_SMC_ECC_MEMCFG_MODE_MASK;
		reg |= mode << PL353_SMC_ECC_MEMCFG_MODE_SHIFT;
		writel(reg, pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);

		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}