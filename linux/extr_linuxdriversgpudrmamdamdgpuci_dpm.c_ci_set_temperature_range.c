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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISLANDS_TEMP_RANGE_MAX ; 
 int /*<<< orphan*/  CISLANDS_TEMP_RANGE_MIN ; 
 int ci_thermal_enable_alert (struct amdgpu_device*,int) ; 
 int ci_thermal_set_temperature_range (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_set_temperature_range(struct amdgpu_device *adev)
{
	int ret;

	ret = ci_thermal_enable_alert(adev, false);
	if (ret)
		return ret;
	ret = ci_thermal_set_temperature_range(adev, CISLANDS_TEMP_RANGE_MIN,
					       CISLANDS_TEMP_RANGE_MAX);
	if (ret)
		return ret;
	ret = ci_thermal_enable_alert(adev, true);
	if (ret)
		return ret;
	return ret;
}