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
struct pp_hwmgr {TYPE_1__ platform_descriptor; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicPatchPowerState ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicPowerManagement ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicUVDState ; 
 int /*<<< orphan*/  PHM_PlatformCaps_EnableSMU7ThermalManagement ; 
 int /*<<< orphan*/  PHM_PlatformCaps_FanSpeedInTableIsRPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PCIEPerformanceRequest ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SMC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDDPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEDPM ; 
 scalar_t__ amdgpu_acpi_is_pcie_performance_request_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hwmgr_init_default_caps(struct pp_hwmgr *hwmgr)
{
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_PCIEPerformanceRequest);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_UVDDPM);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_VCEDPM);

#if defined(CONFIG_ACPI)
	if (amdgpu_acpi_is_pcie_performance_request_supported(hwmgr->adev))
		phm_cap_set(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_PCIEPerformanceRequest);
#endif

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
		PHM_PlatformCaps_DynamicPatchPowerState);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
		PHM_PlatformCaps_EnableSMU7ThermalManagement);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DynamicPowerManagement);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_SMC);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_DynamicUVDState);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
						PHM_PlatformCaps_FanSpeedInTableIsRPM);
	return;
}