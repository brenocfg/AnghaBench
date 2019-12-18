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
struct TYPE_5__ {int usFanOutputSensitivity; int usDefaultFanOutputSensitivity; } ;
struct TYPE_6__ {TYPE_2__ advanceFanControlParameters; } ;
struct pp_hwmgr {TYPE_3__ thermal_controller; scalar_t__ smu_backend; } ;
struct TYPE_4__ {int /*<<< orphan*/  FuzzyFan_PwmSetDelta; } ;
struct polaris10_smumgr {TYPE_1__ power_tune_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_HOST_TO_SMC_US (int) ; 

__attribute__((used)) static int polaris10_populate_fuzzy_fan(struct pp_hwmgr *hwmgr)
{
	struct polaris10_smumgr *smu_data = (struct polaris10_smumgr *)(hwmgr->smu_backend);

/* TO DO move to hwmgr */
	if ((hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity & (1 << 15))
		|| 0 == hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity)
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity =
			hwmgr->thermal_controller.advanceFanControlParameters.usDefaultFanOutputSensitivity;

	smu_data->power_tune_table.FuzzyFan_PwmSetDelta = PP_HOST_TO_SMC_US(
				hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity);
	return 0;
}