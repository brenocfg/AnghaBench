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
 int /*<<< orphan*/  R600_TEMP_RANGE_MAX ; 
 int /*<<< orphan*/  R600_TEMP_RANGE_MIN ; 
 int ci_thermal_enable_alert (struct radeon_device*,int) ; 
 int ci_thermal_set_temperature_range (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_set_temperature_range(struct radeon_device *rdev)
{
	int ret;

	ret = ci_thermal_enable_alert(rdev, false);
	if (ret)
		return ret;
	ret = ci_thermal_set_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
	if (ret)
		return ret;
	ret = ci_thermal_enable_alert(rdev, true);
	if (ret)
		return ret;

	return ret;
}