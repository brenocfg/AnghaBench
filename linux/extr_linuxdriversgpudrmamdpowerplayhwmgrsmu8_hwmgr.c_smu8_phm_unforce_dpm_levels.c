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
struct TYPE_6__ {unsigned long soft_min_clk; unsigned long hard_min_clk; unsigned long soft_max_clk; unsigned long hard_max_clk; } ;
struct smu8_hwmgr {TYPE_3__ sclk_dpm; } ;
struct TYPE_4__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {unsigned long pstate_sclk; scalar_t__ pstate_mclk; TYPE_1__ dyn_state; struct smu8_hwmgr* backend; } ;
struct phm_clock_voltage_dependency_table {unsigned long count; TYPE_2__* entries; } ;
struct TYPE_5__ {unsigned long clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSclkSoftMax ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSclkSoftMin ; 
 int smu8_get_max_sclk_level (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_get_sclk_level (struct pp_hwmgr*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_phm_unforce_dpm_levels(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct phm_clock_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;
	unsigned long clock = 0, level;

	if (NULL == table || table->count <= 0)
		return -EINVAL;

	data->sclk_dpm.soft_min_clk = table->entries[0].clk;
	data->sclk_dpm.hard_min_clk = table->entries[0].clk;
	hwmgr->pstate_sclk = table->entries[0].clk;
	hwmgr->pstate_mclk = 0;

	level = smu8_get_max_sclk_level(hwmgr) - 1;

	if (level < table->count)
		clock = table->entries[level].clk;
	else
		clock = table->entries[table->count - 1].clk;

	data->sclk_dpm.soft_max_clk = clock;
	data->sclk_dpm.hard_max_clk = clock;

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMin,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_min_clk,
				PPSMC_MSG_SetSclkSoftMin));

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMax,
				smu8_get_sclk_level(hwmgr,
				data->sclk_dpm.soft_max_clk,
				PPSMC_MSG_SetSclkSoftMax));

	return 0;
}