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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_SetEnabledMask ; 
 int kv_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kv_set_enabled_level(struct radeon_device *rdev, u32 level)
{
	u32 new_mask = (1 << level);

	return kv_send_msg_to_smc_with_parameter(rdev,
						 PPSMC_MSG_SCLKDPM_SetEnabledMask,
						 new_mask);
}