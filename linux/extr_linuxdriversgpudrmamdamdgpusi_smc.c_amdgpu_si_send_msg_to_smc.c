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
typedef  scalar_t__ u32 ;
struct amdgpu_device {int usec_timeout; } ;
typedef  int /*<<< orphan*/  PPSMC_Result ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_Result_Failed ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MESSAGE_0 ; 
 int /*<<< orphan*/  SMC_RESP_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_si_is_smc_running (struct amdgpu_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

PPSMC_Result amdgpu_si_send_msg_to_smc(struct amdgpu_device *adev,
				       PPSMC_Msg msg)
{
	u32 tmp;
	int i;

	if (!amdgpu_si_is_smc_running(adev))
		return PPSMC_Result_Failed;

	WREG32(SMC_MESSAGE_0, msg);

	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = RREG32(SMC_RESP_0);
		if (tmp != 0)
			break;
		udelay(1);
	}

	return (PPSMC_Result)RREG32(SMC_RESP_0);
}