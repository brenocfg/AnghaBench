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
struct vega20_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 size_t GNLD_PPT ; 
 int /*<<< orphan*/  PPSMC_MSG_SetPptLimit ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vega20_set_power_limit(struct pp_hwmgr *hwmgr, uint32_t n)
{
	struct vega20_hwmgr *data =
			(struct vega20_hwmgr *)(hwmgr->backend);

	if (data->smu_features[GNLD_PPT].enabled)
		return smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetPptLimit, n);

	return 0;
}