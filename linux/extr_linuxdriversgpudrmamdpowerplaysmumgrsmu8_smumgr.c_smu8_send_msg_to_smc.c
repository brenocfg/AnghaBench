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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT ; 
 int PHM_WAIT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_MP1_SRBM2P_RESP_0 ; 
 int smu8_send_msg_to_smc_async (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_send_msg_to_smc(struct pp_hwmgr *hwmgr, uint16_t msg)
{
	int result = 0;

	result = smu8_send_msg_to_smc_async(hwmgr, msg);
	if (result != 0)
		return result;

	return PHM_WAIT_FIELD_UNEQUAL(hwmgr,
					SMU_MP1_SRBM2P_RESP_0, CONTENT, 0);
}