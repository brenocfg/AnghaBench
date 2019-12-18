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
 int /*<<< orphan*/  PPSMC_MSG_GetFeatureStatus ; 
 int smu8_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long smum_get_argument (struct pp_hwmgr*) ; 

__attribute__((used)) static bool smu8_dpm_check_smu_features(struct pp_hwmgr *hwmgr,
				unsigned long check_feature)
{
	int result;
	unsigned long features;

	result = smu8_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetFeatureStatus, 0);
	if (result == 0) {
		features = smum_get_argument(hwmgr);
		if (features & check_feature)
			return true;
	}

	return false;
}