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
 int /*<<< orphan*/  smu8_clear_nb_dpm_flag (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_disable_dpm_tasks (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_power_up_display_clock_sys_pll (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_reset_cc6_data (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_power_off_asic(struct pp_hwmgr *hwmgr)
{
	smu8_disable_dpm_tasks(hwmgr);
	smu8_power_up_display_clock_sys_pll(hwmgr);
	smu8_clear_nb_dpm_flag(hwmgr);
	smu8_reset_cc6_data(hwmgr);
	return 0;
}