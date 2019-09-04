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
struct vega10_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct TYPE_2__ {int supported; int /*<<< orphan*/  smu_feature_bitmap; } ;

/* Variables and functions */
 size_t GNLD_PPT ; 
 size_t GNLD_TDC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerContainment ; 
 int /*<<< orphan*/  PP_ASSERT_WITH_CODE (int,char*,int) ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega10_enable_smc_features (struct pp_hwmgr*,int,int /*<<< orphan*/ ) ; 

int vega10_disable_power_containment(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	if (PP_CAP(PHM_PlatformCaps_PowerContainment)) {
		if (data->smu_features[GNLD_PPT].supported)
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					false, data->smu_features[GNLD_PPT].smu_feature_bitmap),
					"Attempt to disable PPT feature Failed!",
					data->smu_features[GNLD_PPT].supported = false);

		if (data->smu_features[GNLD_TDC].supported)
			PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
					false, data->smu_features[GNLD_TDC].smu_feature_bitmap),
					"Attempt to disable PPT feature Failed!",
					data->smu_features[GNLD_TDC].supported = false);
	}

	return 0;
}