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
typedef  int uint32_t ;
struct ci_single_dpm_table {int count; TYPE_5__* dpm_levels; } ;
struct ci_ps {int performance_level_count; TYPE_4__* performance_levels; } ;
struct TYPE_8__ {struct ci_single_dpm_table mclk_table; } ;
struct ci_power_info {TYPE_3__ golden_dpm_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  requested_ps; } ;
struct TYPE_7__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
struct TYPE_10__ {int value; } ;
struct TYPE_9__ {int mclk; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 struct ci_ps* ci_get_ps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_dpm_set_mclk_od(void *handle, uint32_t value)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);
	struct ci_ps *ps = ci_get_ps(adev->pm.dpm.requested_ps);
	struct ci_single_dpm_table *golden_mclk_table =
			&(pi->golden_dpm_table.mclk_table);

	if (value > 20)
		value = 20;

	ps->performance_levels[ps->performance_level_count - 1].mclk =
			golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value *
			value / 100 +
			golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value;

	return 0;
}