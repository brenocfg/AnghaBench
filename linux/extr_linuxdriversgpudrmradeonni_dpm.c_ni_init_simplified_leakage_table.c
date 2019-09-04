#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct radeon_cac_leakage_table {size_t count; TYPE_5__* entries; } ;
struct TYPE_8__ {struct radeon_cac_leakage_table cac_leakage_table; } ;
struct TYPE_9__ {TYPE_1__ dyn_state; } ;
struct TYPE_10__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_11__ {size_t count; } ;
struct evergreen_power_info {TYPE_4__ vddc_voltage_table; } ;
struct TYPE_13__ {void*** cac_lkge_lut; } ;
struct TYPE_12__ {size_t leakage; } ;
typedef  TYPE_6__ PP_NIslands_CACTABLES ;

/* Variables and functions */
 int EINVAL ; 
 size_t SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES ; 
 size_t SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 size_t ni_get_smc_power_scaling_factor (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_scale_power_for_smc (size_t,size_t) ; 

__attribute__((used)) static int ni_init_simplified_leakage_table(struct radeon_device *rdev,
					    PP_NIslands_CACTABLES *cac_tables)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_cac_leakage_table *leakage_table =
		&rdev->pm.dpm.dyn_state.cac_leakage_table;
	u32 i, j, table_size;
	u32 smc_leakage, max_leakage = 0;
	u32 scaling_factor;

	if (!leakage_table)
		return -EINVAL;

	table_size = leakage_table->count;

	if (eg_pi->vddc_voltage_table.count != table_size)
		table_size = (eg_pi->vddc_voltage_table.count < leakage_table->count) ?
			eg_pi->vddc_voltage_table.count : leakage_table->count;

	if (SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES < table_size)
		table_size = SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES;

	if (table_size == 0)
		return -EINVAL;

	scaling_factor = ni_get_smc_power_scaling_factor(rdev);

	for (j = 0; j < table_size; j++) {
		smc_leakage = leakage_table->entries[j].leakage;

		if (smc_leakage > max_leakage)
			max_leakage = smc_leakage;

		for (i = 0; i < SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES; i++)
			cac_tables->cac_lkge_lut[i][j] =
				cpu_to_be32(ni_scale_power_for_smc(smc_leakage, scaling_factor));
	}

	for (j = table_size; j < SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES; j++) {
		for (i = 0; i < SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES; i++)
			cac_tables->cac_lkge_lut[i][j] =
				cpu_to_be32(ni_scale_power_for_smc(max_leakage, scaling_factor));
	}
	return 0;
}