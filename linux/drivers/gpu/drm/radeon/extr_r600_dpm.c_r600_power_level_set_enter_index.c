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
typedef  enum r600_power_level { ____Placeholder_r600_power_level } r600_power_level ;

/* Variables and functions */
 int /*<<< orphan*/  DYN_PWR_ENTER_INDEX (int) ; 
 int /*<<< orphan*/  DYN_PWR_ENTER_INDEX_MASK ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r600_power_level_set_enter_index(struct radeon_device *rdev,
				      enum r600_power_level index)
{
	WREG32_P(TARGET_AND_CURRENT_PROFILE_INDEX, DYN_PWR_ENTER_INDEX(index),
		 ~DYN_PWR_ENTER_INDEX_MASK);
}