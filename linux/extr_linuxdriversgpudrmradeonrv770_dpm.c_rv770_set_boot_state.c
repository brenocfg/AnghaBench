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
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_SwitchToInitialState ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ rv770_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

int rv770_set_boot_state(struct radeon_device *rdev)
{
	if (rv770_send_msg_to_smc(rdev, PPSMC_MSG_SwitchToInitialState) != PPSMC_Result_OK)
		return -EINVAL;
	return 0;
}