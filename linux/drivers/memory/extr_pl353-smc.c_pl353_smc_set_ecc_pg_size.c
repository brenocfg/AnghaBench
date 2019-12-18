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
 int EINVAL ; 
 scalar_t__ PL353_SMC_ECC_MEMCFG_OFFS ; 
 int PL353_SMC_ECC_MEMCFG_PGSIZE_MASK ; 
#define  SZ_1K 130 
#define  SZ_2K 129 
#define  SZ_512 128 
 scalar_t__ pl353_smc_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int pl353_smc_set_ecc_pg_size(unsigned int pg_sz)
{
	u32 reg, sz;

	switch (pg_sz) {
	case 0:
		sz = 0;
		break;
	case SZ_512:
		sz = 1;
		break;
	case SZ_1K:
		sz = 2;
		break;
	case SZ_2K:
		sz = 3;
		break;
	default:
		return -EINVAL;
	}

	reg = readl(pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);
	reg &= ~PL353_SMC_ECC_MEMCFG_PGSIZE_MASK;
	reg |= sz;
	writel(reg, pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);

	return 0;
}