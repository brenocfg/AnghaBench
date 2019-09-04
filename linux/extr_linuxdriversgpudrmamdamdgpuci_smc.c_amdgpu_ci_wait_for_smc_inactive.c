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
typedef  int u32 ;
struct amdgpu_device {int usec_timeout; } ;
typedef  int /*<<< orphan*/  PPSMC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_Result_OK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SMC_SYSCON_CLOCK_CNTL_0__cken_MASK ; 
 int /*<<< orphan*/  amdgpu_ci_is_smc_running (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixSMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  udelay (int) ; 

PPSMC_Result amdgpu_ci_wait_for_smc_inactive(struct amdgpu_device *adev)
{
	u32 tmp;
	int i;

	if (!amdgpu_ci_is_smc_running(adev))
		return PPSMC_Result_OK;

	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = RREG32_SMC(ixSMC_SYSCON_CLOCK_CNTL_0);
		if ((tmp & SMC_SYSCON_CLOCK_CNTL_0__cken_MASK) == 0)
			break;
		udelay(1);
	}

	return PPSMC_Result_OK;
}