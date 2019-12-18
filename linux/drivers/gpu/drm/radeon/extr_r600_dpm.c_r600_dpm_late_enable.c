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
struct TYPE_3__ {int /*<<< orphan*/  int_thermal_type; } ;
struct radeon_device {TYPE_2__ irq; TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_TEMP_RANGE_MAX ; 
 int /*<<< orphan*/  R600_TEMP_RANGE_MIN ; 
 scalar_t__ r600_is_internal_thermal_sensor (int /*<<< orphan*/ ) ; 
 int r600_set_thermal_temperature_range (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_irq_set (struct radeon_device*) ; 

int r600_dpm_late_enable(struct radeon_device *rdev)
{
	int ret;

	if (rdev->irq.installed &&
	    r600_is_internal_thermal_sensor(rdev->pm.int_thermal_type)) {
		ret = r600_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		if (ret)
			return ret;
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
	}

	return 0;
}