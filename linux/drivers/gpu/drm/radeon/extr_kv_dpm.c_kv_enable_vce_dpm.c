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
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_Enable ; 
 int kv_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_enable_vce_dpm(struct radeon_device *rdev, bool enable)
{
	return kv_notify_message_to_smu(rdev, enable ?
					PPSMC_MSG_VCEDPM_Enable : PPSMC_MSG_VCEDPM_Disable);
}