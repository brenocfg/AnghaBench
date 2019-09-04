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
struct pp_hwmgr {TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_UVDPowerGating ; 
 int phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool phm_cf_want_uvd_power_gating(struct pp_hwmgr *hwmgr)
{
	return phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_UVDPowerGating);
}