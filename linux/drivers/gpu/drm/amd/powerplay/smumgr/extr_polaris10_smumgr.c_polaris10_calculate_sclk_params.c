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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  void* uint16_t ;
struct pp_hwmgr {scalar_t__ adev; scalar_t__ smu_backend; } ;
struct pp_atomctrl_clock_dividers_ai {int usSclk_fcw_frac; size_t ucSclkPllRange; int ucSscEnable; int usSsc_fcw1_frac; int /*<<< orphan*/  usSsc_fcw_slew_frac; void* usSsc_fcw1_int; int /*<<< orphan*/  usPcc_fcw_slew_frac; void* usPcc_fcw_int; void* usSclk_fcw_int; } ;
struct TYPE_9__ {TYPE_2__* SclkFcwRangeTable; } ;
struct polaris10_smumgr {TYPE_1__* range_table; TYPE_4__ smc_state_table; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_8__ {int Fcw_frac; size_t PllRange; int Sclk_slew_rate; int Pcc_down_slew_rate; int SSc_En; int Fcw1_frac; void* Fcw1_int; void* Pcc_fcw_int; void* Fcw_int; int /*<<< orphan*/  Sclk_ss_slew_rate; int /*<<< orphan*/  Pcc_up_slew_rate; scalar_t__ SclkFrequency; } ;
struct TYPE_7__ {scalar_t__ postdiv; } ;
struct TYPE_6__ {scalar_t__ trans_lower_frequency; scalar_t__ trans_upper_frequency; } ;
typedef  TYPE_3__ SMU_SclkSetting ;
typedef  TYPE_4__ SMU74_Discrete_DpmTable ;

/* Variables and functions */
 size_t NUM_SCLK_RANGE ; 
 scalar_t__ amdgpu_asic_get_xclk (struct amdgpu_device*) ; 
 int atomctrl_get_engine_pll_dividers_ai (struct pp_hwmgr*,scalar_t__,struct pp_atomctrl_clock_dividers_ai*) ; 
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 

__attribute__((used)) static int polaris10_calculate_sclk_params(struct pp_hwmgr *hwmgr,
		uint32_t clock, SMU_SclkSetting *sclk_setting)
{
	struct polaris10_smumgr *smu_data = (struct polaris10_smumgr *)(hwmgr->smu_backend);
	const SMU74_Discrete_DpmTable *table = &(smu_data->smc_state_table);
	struct pp_atomctrl_clock_dividers_ai dividers;
	uint32_t ref_clock;
	uint32_t pcc_target_percent, pcc_target_freq, ss_target_percent, ss_target_freq;
	uint8_t i;
	int result;
	uint64_t temp;

	sclk_setting->SclkFrequency = clock;
	/* get the engine clock dividers for this clock value */
	result = atomctrl_get_engine_pll_dividers_ai(hwmgr, clock,  &dividers);
	if (result == 0) {
		sclk_setting->Fcw_int = dividers.usSclk_fcw_int;
		sclk_setting->Fcw_frac = dividers.usSclk_fcw_frac;
		sclk_setting->Pcc_fcw_int = dividers.usPcc_fcw_int;
		sclk_setting->PllRange = dividers.ucSclkPllRange;
		sclk_setting->Sclk_slew_rate = 0x400;
		sclk_setting->Pcc_up_slew_rate = dividers.usPcc_fcw_slew_frac;
		sclk_setting->Pcc_down_slew_rate = 0xffff;
		sclk_setting->SSc_En = dividers.ucSscEnable;
		sclk_setting->Fcw1_int = dividers.usSsc_fcw1_int;
		sclk_setting->Fcw1_frac = dividers.usSsc_fcw1_frac;
		sclk_setting->Sclk_ss_slew_rate = dividers.usSsc_fcw_slew_frac;
		return result;
	}

	ref_clock = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);

	for (i = 0; i < NUM_SCLK_RANGE; i++) {
		if (clock > smu_data->range_table[i].trans_lower_frequency
		&& clock <= smu_data->range_table[i].trans_upper_frequency) {
			sclk_setting->PllRange = i;
			break;
		}
	}

	sclk_setting->Fcw_int = (uint16_t)((clock << table->SclkFcwRangeTable[sclk_setting->PllRange].postdiv) / ref_clock);
	temp = clock << table->SclkFcwRangeTable[sclk_setting->PllRange].postdiv;
	temp <<= 0x10;
	do_div(temp, ref_clock);
	sclk_setting->Fcw_frac = temp & 0xffff;

	pcc_target_percent = 10; /*  Hardcode 10% for now. */
	pcc_target_freq = clock - (clock * pcc_target_percent / 100);
	sclk_setting->Pcc_fcw_int = (uint16_t)((pcc_target_freq << table->SclkFcwRangeTable[sclk_setting->PllRange].postdiv) / ref_clock);

	ss_target_percent = 2; /*  Hardcode 2% for now. */
	sclk_setting->SSc_En = 0;
	if (ss_target_percent) {
		sclk_setting->SSc_En = 1;
		ss_target_freq = clock - (clock * ss_target_percent / 100);
		sclk_setting->Fcw1_int = (uint16_t)((ss_target_freq << table->SclkFcwRangeTable[sclk_setting->PllRange].postdiv) / ref_clock);
		temp = ss_target_freq << table->SclkFcwRangeTable[sclk_setting->PllRange].postdiv;
		temp <<= 0x10;
		do_div(temp, ref_clock);
		sclk_setting->Fcw1_frac = temp & 0xffff;
	}

	return 0;
}