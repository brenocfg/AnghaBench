#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct ni_power_info {scalar_t__ use_power_boost_limit; scalar_t__ enable_power_containment; } ;
struct evergreen_power_info {int /*<<< orphan*/  vddc_voltage_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  vddc; } ;
typedef  int /*<<< orphan*/  NISLANDS_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int div64_u64 (int,int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int ni_get_std_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int ni_populate_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 ni_calculate_power_boost_limit(struct radeon_device *rdev,
					  struct radeon_ps *radeon_state,
					  u32 near_tdp_limit)
{
	struct ni_ps *state = ni_get_ps(radeon_state);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	u32 power_boost_limit = 0;
	int ret;

	if (ni_pi->enable_power_containment &&
	    ni_pi->use_power_boost_limit) {
		NISLANDS_SMC_VOLTAGE_VALUE vddc;
		u16 std_vddc_med;
		u16 std_vddc_high;
		u64 tmp, n, d;

		if (state->performance_level_count < 3)
			return 0;

		ret = ni_populate_voltage_value(rdev, &eg_pi->vddc_voltage_table,
						state->performance_levels[state->performance_level_count - 2].vddc,
						&vddc);
		if (ret)
			return 0;

		ret = ni_get_std_voltage_value(rdev, &vddc, &std_vddc_med);
		if (ret)
			return 0;

		ret = ni_populate_voltage_value(rdev, &eg_pi->vddc_voltage_table,
						state->performance_levels[state->performance_level_count - 1].vddc,
						&vddc);
		if (ret)
			return 0;

		ret = ni_get_std_voltage_value(rdev, &vddc, &std_vddc_high);
		if (ret)
			return 0;

		n = ((u64)near_tdp_limit * ((u64)std_vddc_med * (u64)std_vddc_med) * 90);
		d = ((u64)std_vddc_high * (u64)std_vddc_high * 100);
		tmp = div64_u64(n, d);

		if (tmp >> 32)
			return 0;
		power_boost_limit = (u32)tmp;
	}

	return power_boost_limit;
}