#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vega20_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct pp_display_clock_request {int clock_type; int clock_freq_in_khz; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;
struct TYPE_2__ {scalar_t__ enabled; } ;
typedef  int PPCLK_e ;

/* Variables and functions */
 int EINVAL ; 
 size_t GNLD_DPM_DCEFCLK ; 
 int PPCLK_DCEFCLK ; 
 int PPCLK_DISPCLK ; 
 int PPCLK_PHYCLK ; 
 int PPCLK_PIXCLK ; 
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinByFreq ; 
#define  amd_pp_dcef_clock 131 
#define  amd_pp_disp_clock 130 
#define  amd_pp_phy_clock 129 
#define  amd_pp_pixel_clock 128 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

int vega20_display_clock_voltage_request(struct pp_hwmgr *hwmgr,
		struct pp_display_clock_request *clock_req)
{
	int result = 0;
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	enum amd_pp_clock_type clk_type = clock_req->clock_type;
	uint32_t clk_freq = clock_req->clock_freq_in_khz / 1000;
	PPCLK_e clk_select = 0;
	uint32_t clk_request = 0;

	if (data->smu_features[GNLD_DPM_DCEFCLK].enabled) {
		switch (clk_type) {
		case amd_pp_dcef_clock:
			clk_select = PPCLK_DCEFCLK;
			break;
		case amd_pp_disp_clock:
			clk_select = PPCLK_DISPCLK;
			break;
		case amd_pp_pixel_clock:
			clk_select = PPCLK_PIXCLK;
			break;
		case amd_pp_phy_clock:
			clk_select = PPCLK_PHYCLK;
			break;
		default:
			pr_info("[DisplayClockVoltageRequest]Invalid Clock Type!");
			result = -EINVAL;
			break;
		}

		if (!result) {
			clk_request = (clk_select << 16) | clk_freq;
			result = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinByFreq,
					clk_request);
		}
	}

	return result;
}