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
struct pp_hwmgr {scalar_t__ pptable; } ;
struct phm_ppt_v3_information {scalar_t__ smc_pptable; } ;
struct TYPE_2__ {int /*<<< orphan*/  FanTargetTemperature; } ;
typedef  TYPE_1__ PPTable_t ;

/* Variables and functions */
 int /*<<< orphan*/  VEGA20_FAN_TARGET_TEMPERATURE_OVERRIDE ; 

__attribute__((used)) static int override_powerplay_table_fantargettemperature(struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v3_information *pptable_information =
		(struct phm_ppt_v3_information *)hwmgr->pptable;
	PPTable_t *ppsmc_pptable = (PPTable_t *)(pptable_information->smc_pptable);

	ppsmc_pptable->FanTargetTemperature = VEGA20_FAN_TARGET_TEMPERATURE_OVERRIDE;

	return 0;
}