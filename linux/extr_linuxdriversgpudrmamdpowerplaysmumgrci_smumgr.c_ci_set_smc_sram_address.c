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
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INCREMENT_IND_0 ; 
 int EINVAL ; 
 int /*<<< orphan*/  PHM_WRITE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_IND_ACCESS_CNTL ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSMC_IND_INDEX_0 ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ci_set_smc_sram_address(struct pp_hwmgr *hwmgr,
					uint32_t smc_addr, uint32_t limit)
{
	if ((0 != (3 & smc_addr))
		|| ((smc_addr + 3) >= limit)) {
		pr_err("smc_addr invalid \n");
		return -EINVAL;
	}

	cgs_write_register(hwmgr->device, mmSMC_IND_INDEX_0, smc_addr);
	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, 0);
	return 0;
}