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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_OverDriveSetTargetTdp ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ ci_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_set_overdrive_target_tdp(struct radeon_device *rdev,
				       u32 target_tdp)
{
	PPSMC_Result smc_result =
		ci_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_OverDriveSetTargetTdp, target_tdp);
	if (smc_result != PPSMC_Result_OK)
		return -EINVAL;
	return 0;
}