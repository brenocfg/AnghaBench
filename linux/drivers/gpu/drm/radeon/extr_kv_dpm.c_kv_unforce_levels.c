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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  PPSMC_MSG_NoForcedLevel ; 
 int kv_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int kv_set_enabled_levels (struct radeon_device*) ; 

__attribute__((used)) static int kv_unforce_levels(struct radeon_device *rdev)
{
	if (rdev->family == CHIP_KABINI || rdev->family == CHIP_MULLINS)
		return kv_notify_message_to_smu(rdev, PPSMC_MSG_NoForcedLevel);
	else
		return kv_set_enabled_levels(rdev);
}