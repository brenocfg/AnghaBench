#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  size_t u32 ;
struct TYPE_10__ {size_t count; TYPE_1__* entries; } ;
struct TYPE_11__ {TYPE_2__ uvd_clock_voltage_dependency_table; } ;
struct TYPE_12__ {TYPE_3__ dyn_state; } ;
struct TYPE_13__ {TYPE_4__ dpm; } ;
struct radeon_device {TYPE_5__ pm; } ;
struct atom_clock_dividers {scalar_t__ post_divider; } ;
struct TYPE_15__ {size_t UvdLevelCount; TYPE_6__* UvdLevel; } ;
struct TYPE_14__ {int MinVddc; int MinVddcPhases; void* DclkFrequency; void* VclkFrequency; void* DclkDivider; void* VclkDivider; } ;
struct TYPE_9__ {int v; void* dclk; void* vclk; } ;
typedef  TYPE_7__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int EINVAL ; 
 int VOLTAGE_SCALE ; 
 int cpu_to_be16 (int) ; 
 void* cpu_to_be32 (void*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,void*,int,struct atom_clock_dividers*) ; 

__attribute__((used)) static int ci_populate_smc_uvd_level(struct radeon_device *rdev,
				     SMU7_Discrete_DpmTable *table)
{
	u32 count;
	struct atom_clock_dividers dividers;
	int ret = -EINVAL;

	table->UvdLevelCount =
		rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.count;

	for (count = 0; count < table->UvdLevelCount; count++) {
		table->UvdLevel[count].VclkFrequency =
			rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries[count].vclk;
		table->UvdLevel[count].DclkFrequency =
			rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries[count].dclk;
		table->UvdLevel[count].MinVddc =
			rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries[count].v * VOLTAGE_SCALE;
		table->UvdLevel[count].MinVddcPhases = 1;

		ret = radeon_atom_get_clock_dividers(rdev,
						     COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
						     table->UvdLevel[count].VclkFrequency, false, &dividers);
		if (ret)
			return ret;

		table->UvdLevel[count].VclkDivider = (u8)dividers.post_divider;

		ret = radeon_atom_get_clock_dividers(rdev,
						     COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
						     table->UvdLevel[count].DclkFrequency, false, &dividers);
		if (ret)
			return ret;

		table->UvdLevel[count].DclkDivider = (u8)dividers.post_divider;

		table->UvdLevel[count].VclkFrequency = cpu_to_be32(table->UvdLevel[count].VclkFrequency);
		table->UvdLevel[count].DclkFrequency = cpu_to_be32(table->UvdLevel[count].DclkFrequency);
		table->UvdLevel[count].MinVddc = cpu_to_be16(table->UvdLevel[count].MinVddc);
	}

	return ret;
}