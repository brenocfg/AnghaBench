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
struct pp_hwmgr {scalar_t__ chip_id; TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
 scalar_t__ CHIP_POLARIS10 ; 
 scalar_t__ CHIP_POLARIS11 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_AutomaticDCTransition ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DBRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_EVV ; 
 int /*<<< orphan*/  PHM_PlatformCaps_RegulatorHot ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SPLLShutdownSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SQRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TCPRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TDRamping ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int polaris_set_asic_special_caps(struct pp_hwmgr *hwmgr)
{
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
						PHM_PlatformCaps_EVV);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
						PHM_PlatformCaps_SQRamping);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
						PHM_PlatformCaps_RegulatorHot);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_AutomaticDCTransition);

	if (hwmgr->chip_id != CHIP_POLARIS10)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_SPLLShutdownSupport);

	if (hwmgr->chip_id != CHIP_POLARIS11) {
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
							PHM_PlatformCaps_DBRamping);
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
							PHM_PlatformCaps_TDRamping);
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
							PHM_PlatformCaps_TCPRamping);
	}
	return 0;
}