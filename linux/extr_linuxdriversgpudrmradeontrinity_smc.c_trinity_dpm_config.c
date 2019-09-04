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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_DPM_Config ; 
 int /*<<< orphan*/  SMU_SCRATCH0 ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int trinity_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 

int trinity_dpm_config(struct radeon_device *rdev, bool enable)
{
	if (enable)
		WREG32_SMC(SMU_SCRATCH0, 1);
	else
		WREG32_SMC(SMU_SCRATCH0, 0);

	return trinity_notify_message_to_smu(rdev, PPSMC_MSG_DPM_Config);
}