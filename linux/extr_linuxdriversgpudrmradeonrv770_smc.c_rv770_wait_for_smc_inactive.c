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
struct radeon_device {int usec_timeout; } ;
typedef  int /*<<< orphan*/  PPSMC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_Result_OK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_IO ; 
 int SMC_STOP_MODE ; 
 int /*<<< orphan*/  rv770_is_smc_running (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

PPSMC_Result rv770_wait_for_smc_inactive(struct radeon_device *rdev)
{
	int i;
	PPSMC_Result result = PPSMC_Result_OK;

	if (!rv770_is_smc_running(rdev))
		return result;

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(SMC_IO) & SMC_STOP_MODE)
			break;
		udelay(1);
	}

	return result;
}