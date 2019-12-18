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
typedef  int uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int ATOM_VEGA12_PP_PLATFORM_CAP_BACO ; 
 int ATOM_VEGA12_PP_PLATFORM_CAP_BAMACO ; 
 int ATOM_VEGA12_PP_PLATFORM_CAP_POWERPLAY ; 
 int ATOM_VEGA12_PP_PLATFORM_CAP_SBIOSPOWERSOURCE ; 
 int /*<<< orphan*/  PHM_PlatformCaps_BACO ; 
 int /*<<< orphan*/  PHM_PlatformCaps_BAMACO ; 
 int /*<<< orphan*/  PHM_PlatformCaps_BiosPowerSourceControl ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerPlaySupport ; 
 int /*<<< orphan*/  set_hw_cap (struct pp_hwmgr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_platform_caps(struct pp_hwmgr *hwmgr, uint32_t powerplay_caps)
{
	set_hw_cap(
			hwmgr,
			0 != (powerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_POWERPLAY),
			PHM_PlatformCaps_PowerPlaySupport);

	set_hw_cap(
			hwmgr,
			0 != (powerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_SBIOSPOWERSOURCE),
			PHM_PlatformCaps_BiosPowerSourceControl);

	set_hw_cap(
			hwmgr,
			0 != (powerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_BACO),
			PHM_PlatformCaps_BACO);

	set_hw_cap(
			hwmgr,
			0 != (powerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_BAMACO),
			 PHM_PlatformCaps_BAMACO);

	return 0;
}