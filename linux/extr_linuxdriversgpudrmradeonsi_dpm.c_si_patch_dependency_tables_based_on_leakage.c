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
struct TYPE_5__ {TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int si_patch_single_dependency_table_based_on_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si_patch_dependency_tables_based_on_leakage(struct radeon_device *rdev)
{
	int ret = 0;

	ret = si_patch_single_dependency_table_based_on_leakage(rdev,
								&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk);
	ret = si_patch_single_dependency_table_based_on_leakage(rdev,
								&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk);
	ret = si_patch_single_dependency_table_based_on_leakage(rdev,
								&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk);
	return ret;
}