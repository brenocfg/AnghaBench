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
struct smu8_hwmgr {int disp_clk_bypass_pending; int disp_clk_bypass; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */

__attribute__((used)) static void smu8_power_up_display_clock_sys_pll(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *hw_data = hwmgr->backend;

	hw_data->disp_clk_bypass_pending = false;
	hw_data->disp_clk_bypass = false;
}