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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_FLAGS ; 
 int /*<<< orphan*/  INTERRUPTS_ENABLED ; 
 int /*<<< orphan*/  PHM_WAIT_INDIRECT_FIELD (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SMC_IND ; 
 int /*<<< orphan*/  iceland_start_smc (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  iceland_start_smc_clock (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_program_jump_on_start (struct pp_hwmgr*) ; 

__attribute__((used)) static int iceland_smu_start_smc(struct pp_hwmgr *hwmgr)
{
	/* set smc instruct start point at 0x0 */
	smu7_program_jump_on_start(hwmgr);

	/* enable smc clock */
	iceland_start_smc_clock(hwmgr);

	/* de-assert reset */
	iceland_start_smc(hwmgr);

	PHM_WAIT_INDIRECT_FIELD(hwmgr, SMC_IND, FIRMWARE_FLAGS,
				 INTERRUPTS_ENABLED, 1);

	return 0;
}