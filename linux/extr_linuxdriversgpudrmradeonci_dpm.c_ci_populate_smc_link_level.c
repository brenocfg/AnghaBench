#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  pcie_dpm_enable_mask; } ;
struct TYPE_10__ {void* LinkLevelCount; } ;
struct TYPE_13__ {size_t count; TYPE_1__* dpm_levels; } ;
struct ci_dpm_table {TYPE_7__ pcie_speed_table; } ;
struct ci_power_info {TYPE_4__ dpm_level_enable_mask; TYPE_3__ smc_state_table; struct ci_dpm_table dpm_table; } ;
struct TYPE_12__ {TYPE_2__* LinkLevel; } ;
struct TYPE_9__ {int EnabledForActivity; void* UpT; void* DownT; int /*<<< orphan*/  PcieLaneCount; void* PcieGenSpeed; } ;
struct TYPE_8__ {int /*<<< orphan*/  param1; scalar_t__ value; } ;
typedef  TYPE_5__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  ci_get_dpm_level_enable_mask_value (TYPE_7__*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  r600_encode_pci_lane_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_populate_smc_link_level(struct radeon_device *rdev,
				       SMU7_Discrete_DpmTable *table)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_dpm_table *dpm_table = &pi->dpm_table;
	u32 i;

	for (i = 0; i < dpm_table->pcie_speed_table.count; i++) {
		table->LinkLevel[i].PcieGenSpeed =
			(u8)dpm_table->pcie_speed_table.dpm_levels[i].value;
		table->LinkLevel[i].PcieLaneCount =
			r600_encode_pci_lane_width(dpm_table->pcie_speed_table.dpm_levels[i].param1);
		table->LinkLevel[i].EnabledForActivity = 1;
		table->LinkLevel[i].DownT = cpu_to_be32(5);
		table->LinkLevel[i].UpT = cpu_to_be32(30);
	}

	pi->smc_state_table.LinkLevelCount = (u8)dpm_table->pcie_speed_table.count;
	pi->dpm_level_enable_mask.pcie_dpm_enable_mask =
		ci_get_dpm_level_enable_mask_value(&dpm_table->pcie_speed_table);
}