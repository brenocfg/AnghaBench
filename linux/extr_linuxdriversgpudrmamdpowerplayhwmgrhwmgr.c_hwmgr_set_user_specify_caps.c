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
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {int feature_mask; int od_enabled; TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_CAC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerContainment ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 int PP_OVERDRIVE_MASK ; 
 int PP_POWER_CONTAINMENT_MASK ; 
 int PP_SCLK_DEEP_SLEEP_MASK ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hwmgr_set_user_specify_caps(struct pp_hwmgr *hwmgr)
{
	if (hwmgr->feature_mask & PP_SCLK_DEEP_SLEEP_MASK)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_SclkDeepSleep);
	else
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_SclkDeepSleep);

	if (hwmgr->feature_mask & PP_POWER_CONTAINMENT_MASK) {
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			    PHM_PlatformCaps_PowerContainment);
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_CAC);
	} else {
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			    PHM_PlatformCaps_PowerContainment);
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_CAC);
	}

	if (hwmgr->feature_mask & PP_OVERDRIVE_MASK)
		hwmgr->od_enabled = true;

	return 0;
}