#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int temperature_high; } ;
struct smu7_hwmgr {TYPE_2__ thermal_temp_setting; } ;
struct TYPE_4__ {struct phm_ppm_table* ppm_parameter_table; struct phm_cac_tdp_table* cac_dtp_table; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; scalar_t__ backend; scalar_t__ smu_backend; } ;
struct phm_ppm_table {scalar_t__ tj_max; scalar_t__ dgpu_tdp; } ;
struct phm_cac_tdp_table {int usTDP; int usConfigurableTDP; } ;
struct TYPE_6__ {int GpuTjHyst; int PPM_PkgPwrLimit; int PPM_TemperatureLimit; void**** BAPMTI_RC; void**** BAPMTI_R; int /*<<< orphan*/  BAPM_TEMP_GRADIENT; int /*<<< orphan*/  DTEAmbientTempBase; scalar_t__ GpuTjMax; scalar_t__ DTETjOffset; void* TargetTdp; void* DefaultTdp; } ;
struct ci_smumgr {TYPE_3__ smc_state_table; struct ci_pt_defaults* power_tune_defaults; } ;
struct ci_pt_defaults {int* bapmti_r; int* bapmti_rc; int /*<<< orphan*/  bapm_temp_gradient; int /*<<< orphan*/  dte_ambient_temp_base; } ;
typedef  TYPE_3__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_US (int) ; 
 int /*<<< orphan*/  PP_HOST_TO_SMC_UL (int /*<<< orphan*/ ) ; 
 void* PP_HOST_TO_SMC_US (int const) ; 
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int SMU7_DTE_ITERATIONS ; 
 int SMU7_DTE_SINKS ; 
 int SMU7_DTE_SOURCES ; 

__attribute__((used)) static int ci_populate_bapm_parameters_in_dpm_table(struct pp_hwmgr *hwmgr)
{
	struct ci_smumgr *smu_data = (struct ci_smumgr *)(hwmgr->smu_backend);
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	const struct ci_pt_defaults *defaults = smu_data->power_tune_defaults;
	SMU7_Discrete_DpmTable  *dpm_table = &(smu_data->smc_state_table);
	struct phm_cac_tdp_table *cac_dtp_table = hwmgr->dyn_state.cac_dtp_table;
	struct phm_ppm_table *ppm = hwmgr->dyn_state.ppm_parameter_table;
	const uint16_t *def1, *def2;
	int i, j, k;

	dpm_table->DefaultTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_table->usTDP * 256));
	dpm_table->TargetTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_table->usConfigurableTDP * 256));

	dpm_table->DTETjOffset = 0;
	dpm_table->GpuTjMax = (uint8_t)(data->thermal_temp_setting.temperature_high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES);
	dpm_table->GpuTjHyst = 8;

	dpm_table->DTEAmbientTempBase = defaults->dte_ambient_temp_base;

	if (ppm) {
		dpm_table->PPM_PkgPwrLimit = (uint16_t)ppm->dgpu_tdp * 256 / 1000;
		dpm_table->PPM_TemperatureLimit = (uint16_t)ppm->tj_max * 256;
	} else {
		dpm_table->PPM_PkgPwrLimit = 0;
		dpm_table->PPM_TemperatureLimit = 0;
	}

	CONVERT_FROM_HOST_TO_SMC_US(dpm_table->PPM_PkgPwrLimit);
	CONVERT_FROM_HOST_TO_SMC_US(dpm_table->PPM_TemperatureLimit);

	dpm_table->BAPM_TEMP_GRADIENT = PP_HOST_TO_SMC_UL(defaults->bapm_temp_gradient);
	def1 = defaults->bapmti_r;
	def2 = defaults->bapmti_rc;

	for (i = 0; i < SMU7_DTE_ITERATIONS; i++) {
		for (j = 0; j < SMU7_DTE_SOURCES; j++) {
			for (k = 0; k < SMU7_DTE_SINKS; k++) {
				dpm_table->BAPMTI_R[i][j][k] = PP_HOST_TO_SMC_US(*def1);
				dpm_table->BAPMTI_RC[i][j][k] = PP_HOST_TO_SMC_US(*def2);
				def1++;
				def2++;
			}
		}
	}

	return 0;
}