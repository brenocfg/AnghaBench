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
struct trinity_power_info {scalar_t__ voltage_drop_in_dce; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trinity_add_dccac_value (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_dce_enable_voltage_adjustment (struct radeon_device*,int) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

void trinity_dpm_display_configuration_changed(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	if (pi->voltage_drop_in_dce)
		trinity_dce_enable_voltage_adjustment(rdev, true);
	trinity_add_dccac_value(rdev);
}