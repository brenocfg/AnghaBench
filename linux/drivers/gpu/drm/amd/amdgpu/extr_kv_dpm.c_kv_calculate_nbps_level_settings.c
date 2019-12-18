#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_9__ {size_t* nbp_memory_clock; scalar_t__ nb_dpm_enable; } ;
struct kv_power_info {size_t lowest_valid; size_t highest_valid; TYPE_5__* graphics_level; scalar_t__ battery_state; TYPE_4__ sys_info; scalar_t__ video_start; } ;
struct amdgpu_clock_and_voltage_limits {size_t mclk; } ;
struct TYPE_6__ {struct amdgpu_clock_and_voltage_limits max_clock_voltage_on_ac; } ;
struct TYPE_7__ {int new_active_crtc_count; TYPE_1__ dyn_state; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_3__ pm; } ;
struct TYPE_10__ {int GnbSlow; int ForceNbPs1; int UpH; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int EINVAL ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_calculate_nbps_level_settings(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 i;
	bool force_high;
	struct amdgpu_clock_and_voltage_limits *max_limits =
		&adev->pm.dpm.dyn_state.max_clock_voltage_on_ac;
	u32 mclk = max_limits->mclk;

	if (pi->lowest_valid > pi->highest_valid)
		return -EINVAL;

	if (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) {
		for (i = pi->lowest_valid; i <= pi->highest_valid; i++) {
			pi->graphics_level[i].GnbSlow = 1;
			pi->graphics_level[i].ForceNbPs1 = 0;
			pi->graphics_level[i].UpH = 0;
		}

		if (!pi->sys_info.nb_dpm_enable)
			return 0;

		force_high = ((mclk >= pi->sys_info.nbp_memory_clock[3]) ||
			      (adev->pm.dpm.new_active_crtc_count >= 3) || pi->video_start);

		if (force_high) {
			for (i = pi->lowest_valid; i <= pi->highest_valid; i++)
				pi->graphics_level[i].GnbSlow = 0;
		} else {
			if (pi->battery_state)
				pi->graphics_level[0].ForceNbPs1 = 1;

			pi->graphics_level[1].GnbSlow = 0;
			pi->graphics_level[2].GnbSlow = 0;
			pi->graphics_level[3].GnbSlow = 0;
			pi->graphics_level[4].GnbSlow = 0;
		}
	} else {
		for (i = pi->lowest_valid; i <= pi->highest_valid; i++) {
			pi->graphics_level[i].GnbSlow = 1;
			pi->graphics_level[i].ForceNbPs1 = 0;
			pi->graphics_level[i].UpH = 0;
		}

		if (pi->sys_info.nb_dpm_enable && pi->battery_state) {
			pi->graphics_level[pi->lowest_valid].UpH = 0x28;
			pi->graphics_level[pi->lowest_valid].GnbSlow = 0;
			if (pi->lowest_valid != pi->highest_valid)
				pi->graphics_level[pi->lowest_valid].ForceNbPs1 = 1;
		}
	}
	return 0;
}