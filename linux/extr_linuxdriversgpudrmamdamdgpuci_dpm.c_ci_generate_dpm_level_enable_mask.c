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
struct TYPE_4__ {int /*<<< orphan*/  pcie_speed_table; int /*<<< orphan*/  mclk_table; int /*<<< orphan*/  sclk_table; } ;
struct TYPE_3__ {int mclk_dpm_enable_mask; void* pcie_dpm_enable_mask; void* sclk_dpm_enable_mask; } ;
struct ci_power_info {int last_mclk_dpm_enable_mask; TYPE_2__ dpm_table; TYPE_1__ dpm_level_enable_mask; scalar_t__ uvd_enabled; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 void* ci_get_dpm_level_enable_mask_value (int /*<<< orphan*/ *) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_trim_dpm_states (struct amdgpu_device*,struct amdgpu_ps*) ; 

__attribute__((used)) static int ci_generate_dpm_level_enable_mask(struct amdgpu_device *adev,
					     struct amdgpu_ps *amdgpu_state)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	int ret;

	ret = ci_trim_dpm_states(adev, amdgpu_state);
	if (ret)
		return ret;

	pi->dpm_level_enable_mask.sclk_dpm_enable_mask =
		ci_get_dpm_level_enable_mask_value(&pi->dpm_table.sclk_table);
	pi->dpm_level_enable_mask.mclk_dpm_enable_mask =
		ci_get_dpm_level_enable_mask_value(&pi->dpm_table.mclk_table);
	pi->last_mclk_dpm_enable_mask =
		pi->dpm_level_enable_mask.mclk_dpm_enable_mask;
	if (pi->uvd_enabled) {
		if (pi->dpm_level_enable_mask.mclk_dpm_enable_mask & 1)
			pi->dpm_level_enable_mask.mclk_dpm_enable_mask &= 0xFFFFFFFE;
	}
	pi->dpm_level_enable_mask.pcie_dpm_enable_mask =
		ci_get_dpm_level_enable_mask_value(&pi->dpm_table.pcie_speed_table);

	return 0;
}