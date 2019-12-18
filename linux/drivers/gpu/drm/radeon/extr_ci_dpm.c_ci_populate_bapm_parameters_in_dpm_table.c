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
typedef  void* u8 ;
typedef  int u16 ;
struct radeon_ppm_table {scalar_t__ tj_max; scalar_t__ dgpu_tdp; } ;
struct TYPE_6__ {struct radeon_ppm_table* ppm_table; struct radeon_cac_tdp_table* cac_tdp_table; } ;
struct TYPE_7__ {TYPE_1__ dyn_state; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct radeon_cac_tdp_table {int tdp; int configurable_tdp; } ;
struct ci_pt_defaults {int* bapmti_r; int* bapmti_rc; int /*<<< orphan*/  bapm_temp_gradient; int /*<<< orphan*/  dte_ambient_temp_base; } ;
struct TYPE_9__ {int temperature_high; } ;
struct TYPE_10__ {int DefaultTdp; int TargetTdp; int GpuTjHyst; void**** BAPMTI_RC; void**** BAPMTI_R; int /*<<< orphan*/  BAPM_TEMP_GRADIENT; void* PPM_TemperatureLimit; void* PPM_PkgPwrLimit; int /*<<< orphan*/  DTEAmbientTempBase; void* GpuTjMax; void* DTETjOffset; } ;
struct ci_power_info {TYPE_4__ thermal_temp_setting; scalar_t__ dte_tj_offset; TYPE_5__ smc_state_table; struct ci_pt_defaults* powertune_defaults; } ;
typedef  TYPE_5__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int SMU7_DTE_ITERATIONS ; 
 int SMU7_DTE_SINKS ; 
 int SMU7_DTE_SOURCES ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 void* cpu_to_be16 (int const) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_populate_bapm_parameters_in_dpm_table(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	const struct ci_pt_defaults *pt_defaults = pi->powertune_defaults;
	SMU7_Discrete_DpmTable  *dpm_table = &pi->smc_state_table;
	struct radeon_cac_tdp_table *cac_tdp_table =
		rdev->pm.dpm.dyn_state.cac_tdp_table;
	struct radeon_ppm_table *ppm = rdev->pm.dpm.dyn_state.ppm_table;
	int i, j, k;
	const u16 *def1;
	const u16 *def2;

	dpm_table->DefaultTdp = cac_tdp_table->tdp * 256;
	dpm_table->TargetTdp = cac_tdp_table->configurable_tdp * 256;

	dpm_table->DTETjOffset = (u8)pi->dte_tj_offset;
	dpm_table->GpuTjMax =
		(u8)(pi->thermal_temp_setting.temperature_high / 1000);
	dpm_table->GpuTjHyst = 8;

	dpm_table->DTEAmbientTempBase = pt_defaults->dte_ambient_temp_base;

	if (ppm) {
		dpm_table->PPM_PkgPwrLimit = cpu_to_be16((u16)ppm->dgpu_tdp * 256 / 1000);
		dpm_table->PPM_TemperatureLimit = cpu_to_be16((u16)ppm->tj_max * 256);
	} else {
		dpm_table->PPM_PkgPwrLimit = cpu_to_be16(0);
		dpm_table->PPM_TemperatureLimit = cpu_to_be16(0);
	}

	dpm_table->BAPM_TEMP_GRADIENT = cpu_to_be32(pt_defaults->bapm_temp_gradient);
	def1 = pt_defaults->bapmti_r;
	def2 = pt_defaults->bapmti_rc;

	for (i = 0; i < SMU7_DTE_ITERATIONS; i++) {
		for (j = 0; j < SMU7_DTE_SOURCES; j++) {
			for (k = 0; k < SMU7_DTE_SINKS; k++) {
				dpm_table->BAPMTI_R[i][j][k] = cpu_to_be16(*def1);
				dpm_table->BAPMTI_RC[i][j][k] = cpu_to_be16(*def2);
				def1++;
				def2++;
			}
		}
	}

	return 0;
}