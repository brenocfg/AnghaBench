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
struct smu10_hwmgr {scalar_t__ gfx_off_controled_by_driver; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_DisableGfxOff ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smu10_is_gfx_on (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu10_disable_gfx_off(struct pp_hwmgr *hwmgr)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (smu10_data->gfx_off_controled_by_driver) {
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DisableGfxOff);

		/* confirm gfx is back to "on" state */
		while (!smu10_is_gfx_on(hwmgr))
			msleep(1);
	}

	return 0;
}