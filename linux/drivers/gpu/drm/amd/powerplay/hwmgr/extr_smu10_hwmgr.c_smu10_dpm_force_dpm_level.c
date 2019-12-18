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
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* FClocks; } ;
struct smu10_hwmgr {int gfx_min_freq_limit; int gfx_max_freq_limit; TYPE_2__ clock_table; } ;
struct pp_hwmgr {int smu_version; TYPE_3__* display_config; struct smu10_hwmgr* backend; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
struct TYPE_6__ {int min_core_set_clock; int min_mem_set_clock; int num_display; } ;
struct TYPE_4__ {int Freq; } ;

/* Variables and functions */
#define  AMD_DPM_FORCED_LEVEL_AUTO 136 
#define  AMD_DPM_FORCED_LEVEL_HIGH 135 
#define  AMD_DPM_FORCED_LEVEL_LOW 134 
#define  AMD_DPM_FORCED_LEVEL_MANUAL 133 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_EXIT 132 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK 131 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK 130 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_PEAK 129 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD 128 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinFclkByFreq ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinGfxClk ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinSocclkByFreq ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinVcn ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMaxFclkByFreq ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMaxGfxClk ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMaxSocclkByFreq ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMaxVcn ; 
 int SMU10_UMD_PSTATE_FCLK ; 
 int SMU10_UMD_PSTATE_GFXCLK ; 
 int SMU10_UMD_PSTATE_MIN_SOCCLK ; 
 int SMU10_UMD_PSTATE_MIN_VCE ; 
 int SMU10_UMD_PSTATE_PEAK_FCLK ; 
 int SMU10_UMD_PSTATE_PEAK_SOCCLK ; 
 int SMU10_UMD_PSTATE_SOCCLK ; 
 int SMU10_UMD_PSTATE_VCE ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_dpm_force_dpm_level(struct pp_hwmgr *hwmgr,
				enum amd_dpm_forced_level level)
{
	struct smu10_hwmgr *data = hwmgr->backend;
	uint32_t min_sclk = hwmgr->display_config->min_core_set_clock;
	uint32_t min_mclk = hwmgr->display_config->min_mem_set_clock/100;

	if (hwmgr->smu_version < 0x1E3700) {
		pr_info("smu firmware version too old, can not set dpm level\n");
		return 0;
	}

	if (min_sclk < data->gfx_min_freq_limit)
		min_sclk = data->gfx_min_freq_limit;

	min_sclk /= 100; /* transfer 10KHz to MHz */
	if (min_mclk < data->clock_table.FClocks[0].Freq)
		min_mclk = data->clock_table.FClocks[0].Freq;

	switch (level) {
	case AMD_DPM_FORCED_LEVEL_HIGH:
	case AMD_DPM_FORCED_LEVEL_PROFILE_PEAK:
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						data->gfx_max_freq_limit/100);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						SMU10_UMD_PSTATE_PEAK_FCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinSocclkByFreq,
						SMU10_UMD_PSTATE_PEAK_SOCCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinVcn,
						SMU10_UMD_PSTATE_VCE);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						data->gfx_max_freq_limit/100);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						SMU10_UMD_PSTATE_PEAK_FCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxSocclkByFreq,
						SMU10_UMD_PSTATE_PEAK_SOCCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE);
		break;
	case AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK:
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						min_sclk);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						min_sclk);
		break;
	case AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK:
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						min_mclk);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						min_mclk);
		break;
	case AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD:
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						SMU10_UMD_PSTATE_GFXCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						SMU10_UMD_PSTATE_FCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinSocclkByFreq,
						SMU10_UMD_PSTATE_SOCCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinVcn,
						SMU10_UMD_PSTATE_VCE);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						SMU10_UMD_PSTATE_GFXCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						SMU10_UMD_PSTATE_FCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxSocclkByFreq,
						SMU10_UMD_PSTATE_SOCCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE);
		break;
	case AMD_DPM_FORCED_LEVEL_AUTO:
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						min_sclk);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						hwmgr->display_config->num_display > 3 ?
						SMU10_UMD_PSTATE_PEAK_FCLK :
						min_mclk);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinSocclkByFreq,
						SMU10_UMD_PSTATE_MIN_SOCCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinVcn,
						SMU10_UMD_PSTATE_MIN_VCE);

		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						data->gfx_max_freq_limit/100);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						SMU10_UMD_PSTATE_PEAK_FCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxSocclkByFreq,
						SMU10_UMD_PSTATE_PEAK_SOCCLK);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxVcn,
						SMU10_UMD_PSTATE_VCE);
		break;
	case AMD_DPM_FORCED_LEVEL_LOW:
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinGfxClk,
						data->gfx_min_freq_limit/100);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxGfxClk,
						data->gfx_min_freq_limit/100);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetHardMinFclkByFreq,
						min_mclk);
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SetSoftMaxFclkByFreq,
						min_mclk);
		break;
	case AMD_DPM_FORCED_LEVEL_MANUAL:
	case AMD_DPM_FORCED_LEVEL_PROFILE_EXIT:
	default:
		break;
	}
	return 0;
}