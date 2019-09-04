#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* uint32_t ;
struct smu10_hwmgr {void* dcf_actual_hard_min_freq; void* f_actual_hard_min_freq; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct pp_display_clock_request {int clock_type; int clock_freq_in_khz; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinDcefclkByFreq ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinFclkByFreq ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinSocclkByFreq ; 
#define  amd_pp_dcf_clock 130 
#define  amd_pp_f_clock 129 
#define  amd_pp_soc_clock 128 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int smu10_display_clock_voltage_request(struct pp_hwmgr *hwmgr,
		struct pp_display_clock_request *clock_req)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);
	enum amd_pp_clock_type clk_type = clock_req->clock_type;
	uint32_t clk_freq = clock_req->clock_freq_in_khz / 1000;
	PPSMC_Msg        msg;

	switch (clk_type) {
	case amd_pp_dcf_clock:
		if (clk_freq == smu10_data->dcf_actual_hard_min_freq)
			return 0;
		msg =  PPSMC_MSG_SetHardMinDcefclkByFreq;
		smu10_data->dcf_actual_hard_min_freq = clk_freq;
		break;
	case amd_pp_soc_clock:
		 msg = PPSMC_MSG_SetHardMinSocclkByFreq;
		break;
	case amd_pp_f_clock:
		if (clk_freq == smu10_data->f_actual_hard_min_freq)
			return 0;
		smu10_data->f_actual_hard_min_freq = clk_freq;
		msg = PPSMC_MSG_SetHardMinFclkByFreq;
		break;
	default:
		pr_info("[DisplayClockVoltageRequest]Invalid Clock Type!");
		return -EINVAL;
	}
	smum_send_msg_to_smc_with_parameter(hwmgr, msg, clk_freq);

	return 0;
}