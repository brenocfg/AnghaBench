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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 scalar_t__ PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_disable ; 
 int /*<<< orphan*/  ixSMC_PC_C ; 

bool ci_is_smc_ram_running(struct pp_hwmgr *hwmgr)
{
	return ((0 == PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device,
			CGS_IND_REG__SMC, SMC_SYSCON_CLOCK_CNTL_0, ck_disable))
	&& (0x20100 <= cgs_read_ind_register(hwmgr->device,
			CGS_IND_REG__SMC, ixSMC_PC_C)));
}