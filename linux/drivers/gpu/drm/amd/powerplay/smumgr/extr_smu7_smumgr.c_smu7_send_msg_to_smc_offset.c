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
 int PHM_READ_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WAIT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PPSMC_MSG_Test ; 
 int /*<<< orphan*/  SMC_RESP ; 
 int /*<<< orphan*/  SMC_RESP_0 ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSMC_MESSAGE_0 ; 
 int /*<<< orphan*/  mmSMC_MSG_ARG_0 ; 
 int /*<<< orphan*/  pr_info (char*) ; 

int smu7_send_msg_to_smc_offset(struct pp_hwmgr *hwmgr)
{
	cgs_write_register(hwmgr->device, mmSMC_MSG_ARG_0, 0x20000);

	cgs_write_register(hwmgr->device, mmSMC_MESSAGE_0, PPSMC_MSG_Test);

	PHM_WAIT_FIELD_UNEQUAL(hwmgr, SMC_RESP_0, SMC_RESP, 0);

	if (1 != PHM_READ_FIELD(hwmgr->device, SMC_RESP_0, SMC_RESP))
		pr_info("Failed to send Message.\n");

	return 0;
}