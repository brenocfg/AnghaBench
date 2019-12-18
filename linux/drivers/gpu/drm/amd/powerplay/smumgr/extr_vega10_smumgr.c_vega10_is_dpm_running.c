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
typedef  int uint64_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int SMC_DPM_FEATURES ; 
 int /*<<< orphan*/  vega10_get_enabled_smc_features (struct pp_hwmgr*,int*) ; 

__attribute__((used)) static bool vega10_is_dpm_running(struct pp_hwmgr *hwmgr)
{
	uint64_t features_enabled = 0;

	vega10_get_enabled_smc_features(hwmgr, &features_enabled);

	if (features_enabled & SMC_DPM_FEATURES)
		return true;
	else
		return false;
}