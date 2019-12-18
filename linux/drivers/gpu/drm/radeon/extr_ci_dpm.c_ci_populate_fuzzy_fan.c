#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fan_output_sensitivity; int default_fan_output_sensitivity; } ;
struct TYPE_6__ {TYPE_4__ fan; } ;
struct TYPE_7__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_5__ {int /*<<< orphan*/  FuzzyFan_PwmSetDelta; } ;
struct ci_power_info {TYPE_1__ smc_powertune_table; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static int ci_populate_fuzzy_fan(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);

	if ((rdev->pm.dpm.fan.fan_output_sensitivity & (1 << 15)) ||
	    (rdev->pm.dpm.fan.fan_output_sensitivity == 0))
		rdev->pm.dpm.fan.fan_output_sensitivity =
			rdev->pm.dpm.fan.default_fan_output_sensitivity;

	pi->smc_powertune_table.FuzzyFan_PwmSetDelta =
		cpu_to_be16(rdev->pm.dpm.fan.fan_output_sensitivity);

	return 0;
}