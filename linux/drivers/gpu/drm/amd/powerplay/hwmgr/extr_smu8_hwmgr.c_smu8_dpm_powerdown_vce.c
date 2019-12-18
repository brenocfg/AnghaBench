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
 int /*<<< orphan*/  PHM_PlatformCaps_VCEPowerGating ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEPowerOFF ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_dpm_powerdown_vce(struct pp_hwmgr *hwmgr)
{
	if (PP_CAP(PHM_PlatformCaps_VCEPowerGating))
		return smum_send_msg_to_smc(hwmgr,
						     PPSMC_MSG_VCEPowerOFF);
	return 0;
}