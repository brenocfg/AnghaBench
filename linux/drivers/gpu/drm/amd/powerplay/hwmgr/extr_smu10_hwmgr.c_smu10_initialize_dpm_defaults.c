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
struct smu10_hwmgr {int dce_slow_sclk_threshold; int is_nb_dpm_enabled; int dpm_flags; int need_min_deep_sleep_dcefclk; scalar_t__ deep_sleep_dcefclk; scalar_t__ num_active_display; scalar_t__ thermal_auto_throttling_treshold; } ;
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_PowerPlaySupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SclkThrottleLowNotification ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu10_initialize_dpm_defaults(struct pp_hwmgr *hwmgr)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);

	smu10_data->dce_slow_sclk_threshold = 30000;
	smu10_data->thermal_auto_throttling_treshold = 0;
	smu10_data->is_nb_dpm_enabled = 1;
	smu10_data->dpm_flags = 1;
	smu10_data->need_min_deep_sleep_dcefclk = true;
	smu10_data->num_active_display = 0;
	smu10_data->deep_sleep_dcefclk = 0;

	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_SclkDeepSleep);

	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_SclkThrottleLowNotification);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_PowerPlaySupport);
	return 0;
}