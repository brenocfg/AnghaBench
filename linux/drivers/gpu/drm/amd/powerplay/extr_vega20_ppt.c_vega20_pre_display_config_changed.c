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
struct vega20_dpm_table {int /*<<< orphan*/  mem_table; } ;
struct TYPE_2__ {struct vega20_dpm_table* dpm_context; } ;
struct smu_context {TYPE_1__ smu_dpm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SMU_MSG_NumOfDisplays ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vega20_set_uclk_to_highest_dpm_level (struct smu_context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega20_pre_display_config_changed(struct smu_context *smu)
{
	int ret = 0;
	struct vega20_dpm_table *dpm_table = smu->smu_dpm.dpm_context;

	if (!smu->smu_dpm.dpm_context)
		return -EINVAL;

	smu_send_smc_msg_with_param(smu, SMU_MSG_NumOfDisplays, 0);
	ret = vega20_set_uclk_to_highest_dpm_level(smu,
						   &dpm_table->mem_table);
	if (ret)
		pr_err("Failed to set uclk to highest dpm level");
	return ret;
}