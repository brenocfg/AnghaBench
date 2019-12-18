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
struct smu_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  adev; int /*<<< orphan*/  pm_enabled; } ;
struct amd_pp_display_configuration {int min_dcef_deep_sleep_set_clk; int num_path_including_non_display; int /*<<< orphan*/  nb_pstate_switch_disable; int /*<<< orphan*/  cpu_pstate_disable; int /*<<< orphan*/  cpu_cc6_disable; int /*<<< orphan*/  cpu_pstate_separation_time; TYPE_1__* displays; } ;
struct TYPE_2__ {scalar_t__ controller_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_support_sw_smu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu_set_active_display_count (struct smu_context*,int) ; 
 int /*<<< orphan*/  smu_set_deep_sleep_dcefclk (struct smu_context*,int) ; 
 int /*<<< orphan*/  smu_store_cc6_data (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smu_display_configuration_change(struct smu_context *smu,
				     const struct amd_pp_display_configuration *display_config)
{
	int index = 0;
	int num_of_active_display = 0;

	if (!smu->pm_enabled || !is_support_sw_smu(smu->adev))
		return -EINVAL;

	if (!display_config)
		return -EINVAL;

	mutex_lock(&smu->mutex);

	smu_set_deep_sleep_dcefclk(smu,
				   display_config->min_dcef_deep_sleep_set_clk / 100);

	for (index = 0; index < display_config->num_path_including_non_display; index++) {
		if (display_config->displays[index].controller_id != 0)
			num_of_active_display++;
	}

	smu_set_active_display_count(smu, num_of_active_display);

	smu_store_cc6_data(smu, display_config->cpu_pstate_separation_time,
			   display_config->cpu_cc6_disable,
			   display_config->cpu_pstate_disable,
			   display_config->nb_pstate_switch_disable);

	mutex_unlock(&smu->mutex);

	return 0;
}