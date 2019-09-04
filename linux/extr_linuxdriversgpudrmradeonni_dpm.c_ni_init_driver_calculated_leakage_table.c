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
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_8__ {int leakage_minimum_temperature; int /*<<< orphan*/  i_leakage; int /*<<< orphan*/  leakage_coefficients; } ;
struct ni_power_info {TYPE_3__ cac_data; } ;
struct TYPE_7__ {unsigned int count; TYPE_1__* entries; } ;
struct evergreen_power_info {TYPE_2__ vddc_voltage_table; } ;
typedef  int s32 ;
struct TYPE_9__ {void*** cac_lkge_lut; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ PP_NIslands_CACTABLES ;

/* Variables and functions */
 unsigned int SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES ; 
 unsigned int SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES ; 
 void* cpu_to_be32 (int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_calculate_leakage_for_v_and_t (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int ni_get_smc_power_scaling_factor (struct radeon_device*) ; 
 int ni_scale_power_for_smc (int,int) ; 

__attribute__((used)) static int ni_init_driver_calculated_leakage_table(struct radeon_device *rdev,
						   PP_NIslands_CACTABLES *cac_tables)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 leakage = 0;
	unsigned int i, j, table_size;
	s32 t;
	u32 smc_leakage, max_leakage = 0;
	u32 scaling_factor;

	table_size = eg_pi->vddc_voltage_table.count;

	if (SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES < table_size)
		table_size = SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES;

	scaling_factor = ni_get_smc_power_scaling_factor(rdev);

	for (i = 0; i < SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES; i++) {
		for (j = 0; j < table_size; j++) {
			t = (1000 * ((i + 1) * 8));

			if (t < ni_pi->cac_data.leakage_minimum_temperature)
				t = ni_pi->cac_data.leakage_minimum_temperature;

			ni_calculate_leakage_for_v_and_t(rdev,
							 &ni_pi->cac_data.leakage_coefficients,
							 eg_pi->vddc_voltage_table.entries[j].value,
							 t,
							 ni_pi->cac_data.i_leakage,
							 &leakage);

			smc_leakage = ni_scale_power_for_smc(leakage, scaling_factor) / 1000;
			if (smc_leakage > max_leakage)
				max_leakage = smc_leakage;

			cac_tables->cac_lkge_lut[i][j] = cpu_to_be32(smc_leakage);
		}
	}

	for (j = table_size; j < SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES; j++) {
		for (i = 0; i < SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES; i++)
			cac_tables->cac_lkge_lut[i][j] = cpu_to_be32(max_leakage);
	}
	return 0;
}