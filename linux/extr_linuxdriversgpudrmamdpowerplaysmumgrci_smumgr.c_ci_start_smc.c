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
 int /*<<< orphan*/  FIRMWARE_FLAGS ; 
 int /*<<< orphan*/  INTERRUPTS_ENABLED ; 
 int /*<<< orphan*/  PHM_WAIT_INDIRECT_FIELD (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_IND ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  SMC_SYSCON_RESET_CNTL ; 
 int /*<<< orphan*/  ci_program_jump_on_start (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  ck_disable ; 
 int /*<<< orphan*/  rst_reg ; 

__attribute__((used)) static int ci_start_smc(struct pp_hwmgr *hwmgr)
{
	/* set smc instruct start point at 0x0 */
	ci_program_jump_on_start(hwmgr);

	/* enable smc clock */
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	PHM_WAIT_INDIRECT_FIELD(hwmgr, SMC_IND, FIRMWARE_FLAGS,
				 INTERRUPTS_ENABLED, 1);

	return 0;
}