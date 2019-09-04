#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct TYPE_6__ {unsigned int count; TYPE_3__* entries; } ;
struct ci_power_info {scalar_t__ mvdd_control; TYPE_1__ mvdd_voltage_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  Smio; } ;
struct TYPE_8__ {int /*<<< orphan*/  smio_low; } ;
struct TYPE_7__ {unsigned int MvddLevelCount; TYPE_4__* MvddLevel; } ;
typedef  TYPE_2__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 scalar_t__ CISLANDS_VOLTAGE_CONTROL_BY_GPIO ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_populate_smc_voltage_table (struct radeon_device*,TYPE_3__*,TYPE_4__*) ; 
 unsigned int cpu_to_be32 (unsigned int) ; 

__attribute__((used)) static int ci_populate_smc_mvdd_table(struct radeon_device *rdev,
				      SMU7_Discrete_DpmTable *table)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	unsigned int count;

	table->MvddLevelCount = pi->mvdd_voltage_table.count;
	for (count = 0; count < table->MvddLevelCount; count++) {
		ci_populate_smc_voltage_table(rdev,
					      &pi->mvdd_voltage_table.entries[count],
					      &table->MvddLevel[count]);

		if (pi->mvdd_control == CISLANDS_VOLTAGE_CONTROL_BY_GPIO)
			table->MvddLevel[count].Smio |=
				pi->mvdd_voltage_table.entries[count].smio_low;
		else
			table->MvddLevel[count].Smio = 0;
	}
	table->MvddLevelCount = cpu_to_be32(table->MvddLevelCount);

	return 0;
}