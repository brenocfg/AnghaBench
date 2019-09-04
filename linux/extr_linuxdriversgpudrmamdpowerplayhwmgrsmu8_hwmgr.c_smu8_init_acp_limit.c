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
struct TYPE_6__ {unsigned long soft_max_clk; unsigned long hard_max_clk; scalar_t__ hard_min_clk; scalar_t__ soft_min_clk; } ;
struct smu8_hwmgr {TYPE_3__ acp_dpm; } ;
struct TYPE_4__ {struct phm_acp_clock_voltage_dependency_table* acp_clock_voltage_dependency_table; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; struct smu8_hwmgr* backend; } ;
struct phm_acp_clock_voltage_dependency_table {unsigned long count; TYPE_2__* entries; } ;
struct TYPE_5__ {unsigned long acpclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_GetMaxAclkLevel ; 
 unsigned long smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_init_acp_limit(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct phm_acp_clock_voltage_dependency_table *table =
				hwmgr->dyn_state.acp_clock_voltage_dependency_table;
	unsigned long clock = 0, level;

	if (NULL == table || table->count <= 0)
		return -EINVAL;

	data->acp_dpm.soft_min_clk = 0;
	data->acp_dpm.hard_min_clk = 0;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetMaxAclkLevel);
	level = smum_get_argument(hwmgr);

	if (level < table->count)
		clock = table->entries[level].acpclk;
	else
		clock = table->entries[table->count - 1].acpclk;

	data->acp_dpm.soft_max_clk = clock;
	data->acp_dpm.hard_max_clk = clock;
	return 0;
}