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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ enable_pkg_pwr_tracking_feature; } ;
struct vega10_hwmgr {TYPE_1__ registry_data; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetPptLimit ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vega10_set_power_limit(struct pp_hwmgr *hwmgr, uint32_t n)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->registry_data.enable_pkg_pwr_tracking_feature)
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetPptLimit, n);

	return 0;
}