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
struct smu7_hwmgr {int uvd_power_gated; int vce_power_gated; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu7_powerup_uvd (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_powerup_vce (struct pp_hwmgr*) ; 

int smu7_disable_clock_power_gating(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	data->uvd_power_gated = false;
	data->vce_power_gated = false;

	smu7_powerup_uvd(hwmgr);
	smu7_powerup_vce(hwmgr);

	return 0;
}