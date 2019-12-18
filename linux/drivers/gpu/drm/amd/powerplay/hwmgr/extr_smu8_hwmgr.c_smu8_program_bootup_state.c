#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  soft_max_clk; int /*<<< orphan*/  soft_min_clk; } ;
struct TYPE_4__ {int /*<<< orphan*/  bootup_engine_clock; } ;
struct smu8_hwmgr {TYPE_1__ sclk_dpm; TYPE_2__ sys_info; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetSclkSoftMax ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSclkSoftMin ; 
 int /*<<< orphan*/  smu8_get_sclk_level (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_program_bootup_state(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	data->sclk_dpm.soft_min_clk = data->sys_info.bootup_engine_clock;
	data->sclk_dpm.soft_max_clk = data->sys_info.bootup_engine_clock;

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