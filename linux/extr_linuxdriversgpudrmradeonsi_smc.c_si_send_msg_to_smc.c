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
struct radeon_device {int usec_timeout; } ;
typedef  int /*<<< orphan*/  PPSMC_Result ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_Result_Failed ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MESSAGE_0 ; 
 int /*<<< orphan*/  SMC_RESP_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_is_smc_running (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

PPSMC_Result si_send_msg_to_smc(struct radeon_device *rdev, PPSMC_Msg msg)
{
	u32 tmp;
	int i;

	if (!si_is_smc_running(rdev))
		return PPSMC_Result_Failed;

	WREG32(SMC_MESSAGE_0, msg);

	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(SMC_RESP_0);
		if (tmp != 0)
			break;
		udelay(1);
	}
	tmp = RREG32(SMC_RESP_0);

	return (PPSMC_Result)tmp;
}