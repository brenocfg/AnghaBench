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
struct TYPE_4__ {int /*<<< orphan*/  int_thermal_type; } ;
struct TYPE_3__ {scalar_t__ installed; } ;
struct radeon_device {TYPE_2__ pm; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  R600_TEMP_RANGE_MAX ; 
 int /*<<< orphan*/  R600_TEMP_RANGE_MIN ; 
 int /*<<< orphan*/  kv_dpm_powergate_acp (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_samu (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_uvd (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_vce (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_thermal_int (struct radeon_device*,int) ; 
 int kv_set_thermal_temperature_range (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r600_is_internal_thermal_sensor (int /*<<< orphan*/ ) ; 

int kv_dpm_late_enable(struct radeon_device *rdev)
{
	int ret = 0;

	if (rdev->irq.installed &&
	    r600_is_internal_thermal_sensor(rdev->pm.int_thermal_type)) {
		ret = kv_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		if (ret) {
			DRM_ERROR("kv_set_thermal_temperature_range failed\n");
			return ret;
		}
		kv_enable_thermal_int(rdev, true);
	}

	/* powerdown unused blocks for now */
	kv_dpm_powergate_acp(rdev, true);
	kv_dpm_powergate_samu(rdev, true);
	kv_dpm_powergate_vce(rdev, true);
	kv_dpm_powergate_uvd(rdev, true);

	return ret;
}