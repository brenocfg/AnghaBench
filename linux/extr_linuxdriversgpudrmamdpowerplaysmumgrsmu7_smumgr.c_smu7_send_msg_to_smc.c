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
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int PHM_READ_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WAIT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_RESP ; 
 int /*<<< orphan*/  SMC_RESP_0 ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMC_MESSAGE_0 ; 
 int /*<<< orphan*/  mmSMC_RESP_0 ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 

int smu7_send_msg_to_smc(struct pp_hwmgr *hwmgr, uint16_t msg)
{
	int ret;

	PHM_WAIT_FIELD_UNEQUAL(hwmgr, SMC_RESP_0, SMC_RESP, 0);

	ret = PHM_READ_FIELD(hwmgr->device, SMC_RESP_0, SMC_RESP);

	if (ret == 0xFE)
		pr_debug("last message was not supported\n");
	else if (ret != 1)
		pr_info("\n last message was failed ret is %d\n", ret);

	cgs_write_register(hwmgr->device, mmSMC_RESP_0, 0);
	cgs_write_register(hwmgr->device, mmSMC_MESSAGE_0, msg);

	PHM_WAIT_FIELD_UNEQUAL(hwmgr, SMC_RESP_0, SMC_RESP, 0);

	ret = PHM_READ_FIELD(hwmgr->device, SMC_RESP_0, SMC_RESP);

	if (ret == 0xFE)
		pr_debug("message %x was not supported\n", msg);
	else if (ret != 1)
		pr_info("\n failed to send message %x ret is %d \n",  msg, ret);

	return 0;
}