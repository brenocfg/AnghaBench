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
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MSG_ARG_0 ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PPSMC_Result ci_send_msg_to_smc_return_parameter(struct radeon_device *rdev,
							PPSMC_Msg msg, u32 *parameter)
{
	PPSMC_Result smc_result;

	smc_result = ci_send_msg_to_smc(rdev, msg);

	if ((smc_result == PPSMC_Result_OK) && parameter)
		*parameter = RREG32(SMC_MSG_ARG_0);

	return smc_result;
}