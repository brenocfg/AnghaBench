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
typedef  int /*<<< orphan*/  u32 ;
struct si_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct evergreen_power_info {int /*<<< orphan*/  requested_rps; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 struct si_ps* si_get_ps (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 si_dpm_get_mclk(void *handle, bool low)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct  si_ps *requested_state = si_get_ps(&eg_pi->requested_rps);

	if (low)
		return requested_state->performance_levels[0].mclk;
	else
		return requested_state->performance_levels[requested_state->performance_level_count - 1].mclk;
}