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
struct TYPE_4__ {int dpm_thermal; scalar_t__ installed; } ;
struct TYPE_3__ {scalar_t__ int_thermal_type; } ;
struct radeon_device {TYPE_2__ irq; TYPE_1__ pm; } ;
struct igp_power_info {scalar_t__ gfx_clock_gating; } ;

/* Variables and functions */
 scalar_t__ THERMAL_TYPE_RV6XX ; 
 int /*<<< orphan*/  r600_dynamicpm_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_gfx_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_clk_scaling_enable (struct radeon_device*,int) ; 
 struct igp_power_info* rs780_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_voltage_scaling_enable (struct radeon_device*,int) ; 

void rs780_dpm_disable(struct radeon_device *rdev)
{
	struct igp_power_info *pi = rs780_get_pi(rdev);

	r600_dynamicpm_enable(rdev, false);

	rs780_clk_scaling_enable(rdev, false);
	rs780_voltage_scaling_enable(rdev, false);

	if (pi->gfx_clock_gating)
		r600_gfx_clockgating_enable(rdev, false);

	if (rdev->irq.installed &&
	    (rdev->pm.int_thermal_type == THERMAL_TYPE_RV6XX)) {
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	}
}