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
struct vega12_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 size_t GNLD_DPM_UCLK ; 
 int /*<<< orphan*/  PPSMC_MSG_SetUclkFastSwitch ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vega12_notify_smc_display_change(struct pp_hwmgr *hwmgr,
		bool has_disp)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);

	if (data->smu_features[GNLD_DPM_UCLK].enabled)
		return smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetUclkFastSwitch,
			has_disp ? 1 : 0);

	return 0;
}