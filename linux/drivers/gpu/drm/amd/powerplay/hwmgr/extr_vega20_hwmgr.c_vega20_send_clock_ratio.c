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
struct TYPE_2__ {int /*<<< orphan*/  fclk_gfxclk_ratio; } ;
struct vega20_hwmgr {TYPE_1__ registry_data; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetFclkGfxClkRatio ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_send_clock_ratio(struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data =
			(struct vega20_hwmgr *)(hwmgr->backend);

	return smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetFclkGfxClkRatio,
			data->registry_data.fclk_gfxclk_ratio);
}