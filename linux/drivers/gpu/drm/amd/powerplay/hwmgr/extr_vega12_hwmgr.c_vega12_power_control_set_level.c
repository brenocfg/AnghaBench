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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int TDPAdjustment; scalar_t__ TDPAdjustmentPolarity; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_PowerContainment ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int vega12_set_overdrive_target_percentage (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega12_power_control_set_level(struct pp_hwmgr *hwmgr)
{
	int adjust_percent, result = 0;

	if (PP_CAP(PHM_PlatformCaps_PowerContainment)) {
		adjust_percent =
				hwmgr->platform_descriptor.TDPAdjustmentPolarity ?
				hwmgr->platform_descriptor.TDPAdjustment :
				(-1 * hwmgr->platform_descriptor.TDPAdjustment);
		result = vega12_set_overdrive_target_percentage(hwmgr,
				(uint32_t)adjust_percent);
	}
	return result;
}