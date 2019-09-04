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
struct pp_hwmgr {int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT ; 
 int EINVAL ; 
 int PHM_WAIT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_MP1_SRBM2P_RESP_0 ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMU_MP1_SRBM2P_MSG_0 ; 
 int /*<<< orphan*/  mmSMU_MP1_SRBM2P_RESP_0 ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_send_msg_to_smc_async(struct pp_hwmgr *hwmgr, uint16_t msg)
{
	int result = 0;

	if (hwmgr == NULL || hwmgr->device == NULL)
		return -EINVAL;

	result = PHM_WAIT_FIELD_UNEQUAL(hwmgr,
					SMU_MP1_SRBM2P_RESP_0, CONTENT, 0);
	if (result != 0) {
		pr_err("smu8_send_msg_to_smc_async (0x%04x) failed\n", msg);
		return result;
	}

	cgs_write_register(hwmgr->device, mmSMU_MP1_SRBM2P_RESP_0, 0);
	cgs_write_register(hwmgr->device, mmSMU_MP1_SRBM2P_MSG_0, msg);

	return 0;
}