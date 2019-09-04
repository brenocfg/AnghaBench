#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vddci_dependency_on_mclk; int /*<<< orphan*/  vddc_dependency_on_mclk; int /*<<< orphan*/  vddc_dependency_on_sclk; } ;
struct TYPE_6__ {TYPE_1__ dyn_state; } ;
struct TYPE_5__ {TYPE_3__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int si_patch_single_dependency_table_based_on_leakage (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si_patch_dependency_tables_based_on_leakage(struct amdgpu_device *adev)
{
	int ret = 0;

	ret = si_patch_single_dependency_table_based_on_leakage(adev,
								&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk);
	if (ret)
		DRM_ERROR("Could not patch vddc_on_sclk leakage table\n");
	ret = si_patch_single_dependency_table_based_on_leakage(adev,
								&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk);
	if (ret)
		DRM_ERROR("Could not patch vddc_on_mclk leakage table\n");
	ret = si_patch_single_dependency_table_based_on_leakage(adev,
								&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk);
	if (ret)
		DRM_ERROR("Could not patch vddci_on_mclk leakage table\n");
	return ret;
}