#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  unsigned int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  cac_leakage; } ;
struct si_power_info {TYPE_2__ dyn_powertune_data; TYPE_1__* powertune_data; } ;
struct amdgpu_device {int dummy; } ;
typedef  int s32 ;
struct TYPE_7__ {int /*<<< orphan*/ ** cac_lkge_lut; } ;
struct TYPE_5__ {int /*<<< orphan*/  leakage_coefficients; } ;
typedef  TYPE_3__ PP_SIslands_CacConfig ;

/* Variables and functions */
 unsigned int SMC_SISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES ; 
 unsigned int SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  si_calculate_leakage_for_v_and_t (struct amdgpu_device*,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,int*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int si_get_smc_power_scaling_factor (struct amdgpu_device*) ; 
 int si_scale_power_for_smc (int,int) ; 

__attribute__((used)) static int si_init_dte_leakage_table(struct amdgpu_device *adev,
				     PP_SIslands_CacConfig *cac_tables,
				     u16 vddc_max, u16 vddc_min, u16 vddc_step,
				     u16 t0, u16 t_step)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	u32 leakage;
	unsigned int i, j;
	s32 t;
	u32 smc_leakage;
	u32 scaling_factor;
	u16 voltage;

	scaling_factor = si_get_smc_power_scaling_factor(adev);

	for (i = 0; i < SMC_SISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES ; i++) {
		t = (1000 * (i * t_step + t0));

		for (j = 0; j < SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES; j++) {
			voltage = vddc_max - (vddc_step * j);

			si_calculate_leakage_for_v_and_t(adev,
							 &si_pi->powertune_data->leakage_coefficients,
							 voltage,
							 t,
							 si_pi->dyn_powertune_data.cac_leakage,
							 &leakage);

			smc_leakage = si_scale_power_for_smc(leakage, scaling_factor) / 4;

			if (smc_leakage > 0xFFFF)
				smc_leakage = 0xFFFF;

			cac_tables->cac_lkge_lut[i][SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES-1-j] =
				cpu_to_be16((u16)smc_leakage);
		}
	}
	return 0;
}