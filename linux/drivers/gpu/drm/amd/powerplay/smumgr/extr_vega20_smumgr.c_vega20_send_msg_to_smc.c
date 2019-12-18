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
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MP1 ; 
 int PPSMC_Result_OK ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMP1_SMN_C2PMSG_90 ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vega20_send_msg_to_smc_without_waiting (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int vega20_wait_for_response (struct pp_hwmgr*) ; 

__attribute__((used)) static int vega20_send_msg_to_smc(struct pp_hwmgr *hwmgr, uint16_t msg)
{
	struct amdgpu_device *adev = hwmgr->adev;
	int ret = 0;

	vega20_wait_for_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	vega20_send_msg_to_smc_without_waiting(hwmgr, msg);

	ret = vega20_wait_for_response(hwmgr);
	if (ret != PPSMC_Result_OK)
		pr_err("Failed to send message 0x%x, response 0x%x\n", msg, ret);

	return (ret == PPSMC_Result_OK) ? 0 : -EIO;
}