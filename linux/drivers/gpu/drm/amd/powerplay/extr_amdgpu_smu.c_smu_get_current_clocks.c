#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smu_context {int /*<<< orphan*/  mutex; scalar_t__ support_power_containment; int /*<<< orphan*/  adev; } ;
struct smu_clock_info {int /*<<< orphan*/  min_eng_clk; int /*<<< orphan*/  max_eng_clk; int /*<<< orphan*/  max_bus_bandwidth; int /*<<< orphan*/  min_bus_bandwidth; int /*<<< orphan*/  max_mem_clk; int /*<<< orphan*/  min_mem_clk; } ;
struct amd_pp_simple_clock_info {scalar_t__ level; int /*<<< orphan*/  member_0; } ;
struct amd_pp_clock_info {scalar_t__ max_clocks_state; int /*<<< orphan*/  min_engine_clock_in_sr; int /*<<< orphan*/  max_engine_clock_in_sr; int /*<<< orphan*/  max_bus_bandwidth; int /*<<< orphan*/  min_bus_bandwidth; int /*<<< orphan*/  max_memory_clock; int /*<<< orphan*/  min_memory_clock; int /*<<< orphan*/  max_engine_clock; int /*<<< orphan*/  min_engine_clock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PERF_LEVEL_ACTIVITY ; 
 int /*<<< orphan*/  PERF_LEVEL_POWER_CONTAINMENT ; 
 scalar_t__ PP_DAL_POWERLEVEL_7 ; 
 int /*<<< orphan*/  is_support_sw_smu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_get_clock_info (struct smu_context*,struct smu_clock_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_get_current_shallow_sleep_clocks (struct smu_context*,struct smu_clock_info*) ; 
 int /*<<< orphan*/  smu_get_dal_power_level (struct smu_context*,struct amd_pp_simple_clock_info*) ; 

int smu_get_current_clocks(struct smu_context *smu,
			   struct amd_pp_clock_info *clocks)
{
	struct amd_pp_simple_clock_info simple_clocks = {0};
	struct smu_clock_info hw_clocks;
	int ret = 0;

	if (!is_support_sw_smu(smu->adev))
		return -EINVAL;

	mutex_lock(&smu->mutex);

	smu_get_dal_power_level(smu, &simple_clocks);

	if (smu->support_power_containment)
		ret = smu_get_clock_info(smu, &hw_clocks,
					 PERF_LEVEL_POWER_CONTAINMENT);
	else
		ret = smu_get_clock_info(smu, &hw_clocks, PERF_LEVEL_ACTIVITY);

	if (ret) {
		pr_err("Error in smu_get_clock_info\n");
		goto failed;
	}

	clocks->min_engine_clock = hw_clocks.min_eng_clk;
	clocks->max_engine_clock = hw_clocks.max_eng_clk;
	clocks->min_memory_clock = hw_clocks.min_mem_clk;
	clocks->max_memory_clock = hw_clocks.max_mem_clk;
	clocks->min_bus_bandwidth = hw_clocks.min_bus_bandwidth;
	clocks->max_bus_bandwidth = hw_clocks.max_bus_bandwidth;
	clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
	clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;

        if (simple_clocks.level == 0)
                clocks->max_clocks_state = PP_DAL_POWERLEVEL_7;
        else
                clocks->max_clocks_state = simple_clocks.level;

        if (!smu_get_current_shallow_sleep_clocks(smu, &hw_clocks)) {
                clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
                clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;
        }

failed:
	mutex_unlock(&smu->mutex);
	return ret;
}