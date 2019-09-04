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
 int /*<<< orphan*/  SMU_EnabledFeatureScoreboard_SclkDpmOn ; 
 scalar_t__ smu8_dpm_check_smu_features (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool smu8_is_dpm_running(struct pp_hwmgr *hwmgr)
{
	if (smu8_dpm_check_smu_features(hwmgr, SMU_EnabledFeatureScoreboard_SclkDpmOn))
		return true;
	return false;
}