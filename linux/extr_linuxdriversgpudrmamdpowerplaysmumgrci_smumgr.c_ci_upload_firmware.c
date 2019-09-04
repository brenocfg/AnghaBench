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
 int /*<<< orphan*/  PHM_WAIT_INDIRECT_FIELD (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RCU_UC_EVENTS ; 
 int /*<<< orphan*/  SMC_IND ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  SMC_SYSCON_MISC_CNTL ; 
 int /*<<< orphan*/  SMC_SYSCON_RESET_CNTL ; 
 int /*<<< orphan*/  boot_seq_done ; 
 scalar_t__ ci_is_smc_ram_running (struct pp_hwmgr*) ; 
 int ci_load_smc_ucode (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  ck_disable ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pre_fetcher_en ; 
 int /*<<< orphan*/  rst_reg ; 

__attribute__((used)) static int ci_upload_firmware(struct pp_hwmgr *hwmgr)
{
	if (ci_is_smc_ram_running(hwmgr)) {
		pr_info("smc is running, no need to load smc firmware\n");
		return 0;
	}
	PHM_WAIT_INDIRECT_FIELD(hwmgr, SMC_IND, RCU_UC_EVENTS,
			boot_seq_done, 1);
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SMC_SYSCON_MISC_CNTL,
			pre_fetcher_en, 1);

	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 1);
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SMC_SYSCON_RESET_CNTL, rst_reg, 1);
	return ci_load_smc_ucode(hwmgr);
}