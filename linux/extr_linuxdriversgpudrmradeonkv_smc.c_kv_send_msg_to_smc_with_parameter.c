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
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_MSG_ARG_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kv_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 

int kv_send_msg_to_smc_with_parameter(struct radeon_device *rdev,
				      PPSMC_Msg msg, u32 parameter)
{

	WREG32(SMC_MSG_ARG_0, parameter);

	return kv_notify_message_to_smu(rdev, msg);
}