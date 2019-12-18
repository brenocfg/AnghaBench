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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct TYPE_10__ {size_t count; TYPE_1__* entries; } ;
struct TYPE_11__ {TYPE_2__ samu_clock_voltage_dependency_table; } ;
struct TYPE_12__ {TYPE_3__ dyn_state; } ;
struct TYPE_13__ {TYPE_4__ dpm; } ;
struct radeon_device {TYPE_5__ pm; } ;
struct atom_clock_dividers {scalar_t__ post_divider; } ;
struct TYPE_15__ {size_t SamuLevelCount; TYPE_6__* SamuLevel; } ;
struct TYPE_14__ {int MinVoltage; int MinPhases; int /*<<< orphan*/  Frequency; scalar_t__ Divider; } ;
struct TYPE_9__ {int v; int /*<<< orphan*/  clk; } ;
typedef  TYPE_7__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int EINVAL ; 
 int VOLTAGE_SCALE ; 
 int cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 

__attribute__((used)) static int ci_populate_smc_samu_level(struct radeon_device *rdev,
				      SMU7_Discrete_DpmTable *table)
{
	u32 count;
	struct atom_clock_dividers dividers;
	int ret = -EINVAL;

	table->SamuLevelCount =
		rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.count;

	for (count = 0; count < table->SamuLevelCount; count++) {
		table->SamuLevel[count].Frequency =
			rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.entries[count].clk;
		table->SamuLevel[count].MinVoltage =
			rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.entries[count].v * VOLTAGE_SCALE;
		table->SamuLevel[count].MinPhases = 1;

		ret = radeon_atom_get_clock_dividers(rdev,
						     COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
						     table->SamuLevel[count].Frequency, false, &dividers);
		if (ret)
			return ret;

		table->SamuLevel[count].Divider = (u8)dividers.post_divider;

		table->SamuLevel[count].Frequency = cpu_to_be32(table->SamuLevel[count].Frequency);
		table->SamuLevel[count].MinVoltage = cpu_to_be16(table->SamuLevel[count].MinVoltage);
	}

	return ret;
}