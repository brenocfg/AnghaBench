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
typedef  scalar_t__ PPSMC_Result ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_SMC_MSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_SMC_MSG_MASK ; 
 int HOST_SMC_RESP_MASK ; 
 int HOST_SMC_RESP_SHIFT ; 
 scalar_t__ PPSMC_Result_Failed ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MSG ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_is_smc_running (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

PPSMC_Result rv770_send_msg_to_smc(struct radeon_device *rdev, PPSMC_Msg msg)
{
	u32 tmp;
	int i;
	PPSMC_Result result;

	if (!rv770_is_smc_running(rdev))
		return PPSMC_Result_Failed;

	WREG32_P(SMC_MSG, HOST_SMC_MSG(msg), ~HOST_SMC_MSG_MASK);

	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(SMC_MSG) & HOST_SMC_RESP_MASK;
		tmp >>= HOST_SMC_RESP_SHIFT;
		if (tmp != 0)
			break;
		udelay(1);
	}

	tmp = RREG32(SMC_MSG) & HOST_SMC_RESP_MASK;
	tmp >>= HOST_SMC_RESP_SHIFT;

	result = (PPSMC_Result)tmp;
	return result;
}