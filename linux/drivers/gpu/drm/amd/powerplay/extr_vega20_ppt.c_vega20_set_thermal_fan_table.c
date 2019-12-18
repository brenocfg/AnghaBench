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
struct smu_table_context {TYPE_1__* driver_pptable; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct TYPE_2__ {scalar_t__ FanTargetTemperature; } ;
typedef  TYPE_1__ PPTable_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_SetFanTemperatureTarget ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_set_thermal_fan_table(struct smu_context *smu)
{
	int ret;
	struct smu_table_context *table_context = &smu->smu_table;
	PPTable_t *pptable = table_context->driver_pptable;

	ret = smu_send_smc_msg_with_param(smu, SMU_MSG_SetFanTemperatureTarget,
			(uint32_t)pptable->FanTargetTemperature);

	return ret;
}