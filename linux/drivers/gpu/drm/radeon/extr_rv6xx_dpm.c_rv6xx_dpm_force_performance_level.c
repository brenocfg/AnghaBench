#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rv6xx_power_info {int restricted_levels; } ;
struct TYPE_3__ {int forced_level; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
typedef  enum radeon_dpm_forced_level { ____Placeholder_radeon_dpm_forced_level } radeon_dpm_forced_level ;

/* Variables and functions */
 int /*<<< orphan*/  R600_POWER_LEVEL_HIGH ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_LOW ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_MEDIUM ; 
 int RADEON_DPM_FORCED_LEVEL_HIGH ; 
 int RADEON_DPM_FORCED_LEVEL_LOW ; 
 int /*<<< orphan*/  r600_power_level_enable (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_set_at (struct radeon_device*,int,int,int,int) ; 
 int /*<<< orphan*/  r600_wait_for_power_level (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv6xx_clear_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_enable_high (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_enable_medium (struct radeon_device*) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_at (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_vc (struct radeon_device*) ; 

int rv6xx_dpm_force_performance_level(struct radeon_device *rdev,
				      enum radeon_dpm_forced_level level)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	if (level == RADEON_DPM_FORCED_LEVEL_HIGH) {
		pi->restricted_levels = 3;
	} else if (level == RADEON_DPM_FORCED_LEVEL_LOW) {
		pi->restricted_levels = 2;
	} else {
		pi->restricted_levels = 0;
	}

	rv6xx_clear_vc(rdev);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_set_at(rdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
	r600_wait_for_power_level(rdev, R600_POWER_LEVEL_LOW);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);
	rv6xx_enable_medium(rdev);
	rv6xx_enable_high(rdev);
	if (pi->restricted_levels == 3)
		r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, false);
	rv6xx_program_vc(rdev);
	rv6xx_program_at(rdev);

	rdev->pm.dpm.forced_level = level;

	return 0;
}