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
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP1 ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmMP1_SMN_C2PMSG_82 ; 
 int /*<<< orphan*/  mmMP1_SMN_C2PMSG_90 ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smu9_send_msg_to_smc_without_waiting (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int smu9_wait_for_response (struct pp_hwmgr*) ; 

int smu9_send_msg_to_smc_with_parameter(struct pp_hwmgr *hwmgr,
					uint16_t msg, uint32_t parameter)
{
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t ret;

	smu9_wait_for_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, parameter);

	smu9_send_msg_to_smc_without_waiting(hwmgr, msg);

	ret = smu9_wait_for_response(hwmgr);
	if (ret != 1)
		pr_err("Failed message: 0x%x, input parameter: 0x%x, error code: 0x%x\n", msg, parameter, ret);

	return 0;
}