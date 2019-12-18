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
struct radeon_device {int usec_timeout; } ;
typedef  int /*<<< orphan*/  PPSMC_Result ;

/* Variables and functions */
 int CKEN ; 
 int /*<<< orphan*/  PPSMC_Result_OK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  si_is_smc_running (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

PPSMC_Result si_wait_for_smc_inactive(struct radeon_device *rdev)
{
	u32 tmp;
	int i;

	if (!si_is_smc_running(rdev))
		return PPSMC_Result_OK;

	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);
		if ((tmp & CKEN) == 0)
			break;
		udelay(1);
	}

	return PPSMC_Result_OK;
}