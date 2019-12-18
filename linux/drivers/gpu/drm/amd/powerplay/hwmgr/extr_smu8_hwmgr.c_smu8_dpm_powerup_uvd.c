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
 int /*<<< orphan*/  PHM_PlatformCaps_UVDDynamicPowerGating ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDPowerGating ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDPowerON ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu8_dpm_powerup_uvd(struct pp_hwmgr *hwmgr)
{
	if (PP_CAP(PHM_PlatformCaps_UVDPowerGating)) {
		return smum_send_msg_to_smc_with_parameter(
			hwmgr,
			PPSMC_MSG_UVDPowerON,
			PP_CAP(PHM_PlatformCaps_UVDDynamicPowerGating) ? 1 : 0);
	}

	return 0;
}