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
 int /*<<< orphan*/  PPSMC_MSG_ResetToDefaults ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ si_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_reset_to_default(struct radeon_device *rdev)
{
	return (si_send_msg_to_smc(rdev, PPSMC_MSG_ResetToDefaults) == PPSMC_Result_OK) ?
		0 : -EINVAL;
}