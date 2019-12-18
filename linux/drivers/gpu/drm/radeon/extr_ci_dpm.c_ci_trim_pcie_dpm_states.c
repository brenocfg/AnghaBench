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
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct ci_single_dpm_table {size_t count; TYPE_2__* dpm_levels; } ;
struct TYPE_3__ {struct ci_single_dpm_table pcie_speed_table; } ;
struct ci_power_info {TYPE_1__ dpm_table; } ;
struct TYPE_4__ {size_t value; size_t param1; int enabled; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ci_trim_pcie_dpm_states(struct radeon_device *rdev,
				    u32 speed_low, u32 lanes_low,
				    u32 speed_high, u32 lanes_high)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_single_dpm_table *pcie_table = &pi->dpm_table.pcie_speed_table;
	u32 i, j;

	for (i = 0; i < pcie_table->count; i++) {
		if ((pcie_table->dpm_levels[i].value < speed_low) ||
		    (pcie_table->dpm_levels[i].param1 < lanes_low) ||
		    (pcie_table->dpm_levels[i].value > speed_high) ||
		    (pcie_table->dpm_levels[i].param1 > lanes_high))
			pcie_table->dpm_levels[i].enabled = false;
		else
			pcie_table->dpm_levels[i].enabled = true;
	}

	for (i = 0; i < pcie_table->count; i++) {
		if (pcie_table->dpm_levels[i].enabled) {
			for (j = i + 1; j < pcie_table->count; j++) {
				if (pcie_table->dpm_levels[j].enabled) {
					if ((pcie_table->dpm_levels[i].value == pcie_table->dpm_levels[j].value) &&
					    (pcie_table->dpm_levels[i].param1 == pcie_table->dpm_levels[j].param1))
						pcie_table->dpm_levels[j].enabled = false;
				}
			}
		}
	}
}