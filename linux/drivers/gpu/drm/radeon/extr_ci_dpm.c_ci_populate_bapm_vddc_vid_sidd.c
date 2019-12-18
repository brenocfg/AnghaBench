#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_11__ {int count; TYPE_3__* entries; } ;
struct TYPE_9__ {int count; } ;
struct TYPE_12__ {TYPE_4__ cac_leakage_table; TYPE_2__ vddc_dependency_on_sclk; } ;
struct TYPE_13__ {int platform_caps; TYPE_5__ dyn_state; } ;
struct TYPE_14__ {TYPE_6__ dpm; } ;
struct radeon_device {TYPE_7__ pm; } ;
struct TYPE_8__ {int /*<<< orphan*/ * BapmVddCVidHiSidd2; int /*<<< orphan*/ * BapmVddCVidLoSidd; int /*<<< orphan*/ * BapmVddCVidHiSidd; } ;
struct ci_power_info {TYPE_1__ smc_powertune_table; } ;
struct TYPE_10__ {scalar_t__ leakage; int /*<<< orphan*/  vddc; int /*<<< orphan*/  vddc3; int /*<<< orphan*/  vddc2; int /*<<< orphan*/  vddc1; } ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_EVV ; 
 int EINVAL ; 
 int /*<<< orphan*/  ci_convert_to_vid (int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_populate_bapm_vddc_vid_sidd(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u8 *hi_vid = pi->smc_powertune_table.BapmVddCVidHiSidd;
	u8 *lo_vid = pi->smc_powertune_table.BapmVddCVidLoSidd;
	u8 *hi2_vid = pi->smc_powertune_table.BapmVddCVidHiSidd2;
	u32 i;

	if (rdev->pm.dpm.dyn_state.cac_leakage_table.entries == NULL)
		return -EINVAL;
	if (rdev->pm.dpm.dyn_state.cac_leakage_table.count > 8)
		return -EINVAL;
	if (rdev->pm.dpm.dyn_state.cac_leakage_table.count !=
	    rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count)
		return -EINVAL;

	for (i = 0; i < rdev->pm.dpm.dyn_state.cac_leakage_table.count; i++) {
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_EVV) {
			lo_vid[i] = ci_convert_to_vid(rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc1);
			hi_vid[i] = ci_convert_to_vid(rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc2);
			hi2_vid[i] = ci_convert_to_vid(rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc3);
		} else {
			lo_vid[i] = ci_convert_to_vid(rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc);
			hi_vid[i] = ci_convert_to_vid((u16)rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].leakage);
		}
	}
	return 0;
}