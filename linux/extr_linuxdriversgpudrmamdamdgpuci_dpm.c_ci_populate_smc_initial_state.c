#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ci_ps {TYPE_8__* performance_levels; } ;
struct TYPE_18__ {size_t GraphicsBootLevel; size_t MemoryBootLevel; } ;
struct ci_power_info {TYPE_9__ smc_state_table; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_13__ {size_t count; TYPE_3__* entries; } ;
struct TYPE_11__ {size_t count; TYPE_1__* entries; } ;
struct TYPE_14__ {TYPE_4__ vddc_dependency_on_mclk; TYPE_2__ vddc_dependency_on_sclk; } ;
struct TYPE_15__ {TYPE_5__ dyn_state; } ;
struct TYPE_16__ {TYPE_6__ dpm; } ;
struct amdgpu_device {TYPE_7__ pm; } ;
struct TYPE_17__ {scalar_t__ sclk; scalar_t__ mclk; } ;
struct TYPE_12__ {scalar_t__ clk; } ;
struct TYPE_10__ {scalar_t__ clk; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 struct ci_ps* ci_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static void ci_populate_smc_initial_state(struct amdgpu_device *adev,
					  struct amdgpu_ps *amdgpu_boot_state)
{
	struct ci_ps *boot_state = ci_get_ps(amdgpu_boot_state);
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 level = 0;

	for (level = 0; level < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; level++) {
		if (adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[level].clk >=
		    boot_state->performance_levels[0].sclk) {
			pi->smc_state_table.GraphicsBootLevel = level;
			break;
		}
	}

	for (level = 0; level < adev->pm.dpm.dyn_state.vddc_dependency_on_mclk.count; level++) {
		if (adev->pm.dpm.dyn_state.vddc_dependency_on_mclk.entries[level].clk >=
		    boot_state->performance_levels[0].mclk) {
			pi->smc_state_table.MemoryBootLevel = level;
			break;
		}
	}
}