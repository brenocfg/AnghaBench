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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_BacoWorkAroundFlushVDCI ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int vega20_set_pptable_driver_address (struct pp_hwmgr*) ; 

int vega20_baco_apply_vdci_flush_workaround(struct pp_hwmgr *hwmgr)
{
	int ret = 0;

	ret = vega20_set_pptable_driver_address(hwmgr);
	if (ret)
		return ret;

	return smum_send_msg_to_smc(hwmgr, PPSMC_MSG_BacoWorkAroundFlushVDCI);
}