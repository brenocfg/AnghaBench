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
struct pp_hwmgr {TYPE_1__* display_config; } ;
struct TYPE_2__ {int num_display; int /*<<< orphan*/  multi_monitor_in_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu7_notify_smc_display_change (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int
smu7_notify_smc_display_config_after_ps_adjustment(struct pp_hwmgr *hwmgr)
{
	if (hwmgr->display_config->num_display > 1 &&
			!hwmgr->display_config->multi_monitor_in_sync)
		smu7_notify_smc_display_change(hwmgr, false);

	return 0;
}