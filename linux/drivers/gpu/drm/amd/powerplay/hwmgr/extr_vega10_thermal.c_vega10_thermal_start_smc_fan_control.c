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
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega10_fan_ctrl_start_smc_fan_control (struct pp_hwmgr*) ; 

int vega10_thermal_start_smc_fan_control(struct pp_hwmgr *hwmgr)
{
/* If the fantable setup has failed we could have disabled
 * PHM_PlatformCaps_MicrocodeFanControl even after
 * this function was included in the table.
 * Make sure that we still think controlling the fan is OK.
*/
	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		vega10_fan_ctrl_start_smc_fan_control(hwmgr);

	return 0;
}