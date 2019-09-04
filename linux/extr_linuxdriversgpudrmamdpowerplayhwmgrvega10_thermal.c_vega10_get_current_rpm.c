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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_GetCurrentRpm ; 
 int /*<<< orphan*/  smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_get_current_rpm(struct pp_hwmgr *hwmgr, uint32_t *current_rpm)
{
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentRpm);
	*current_rpm = smum_get_argument(hwmgr);
	return 0;
}