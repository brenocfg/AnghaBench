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
struct smu_performance_level {int non_local_mem_freq; int non_local_mem_width; int /*<<< orphan*/  core_clock; int /*<<< orphan*/  memory_clock; int /*<<< orphan*/  member_0; } ;
struct smu_context {int dummy; } ;
struct smu_clock_info {int min_bus_bandwidth; int /*<<< orphan*/  min_eng_clk; int /*<<< orphan*/  min_mem_clk; } ;
typedef  enum smu_perf_level_designation { ____Placeholder_smu_perf_level_designation } smu_perf_level_designation ;

/* Variables and functions */
 int EINVAL ; 
 int PERF_LEVEL_ACTIVITY ; 
 int smu_get_perf_level (struct smu_context*,int,struct smu_performance_level*) ; 

__attribute__((used)) static int smu_get_clock_info(struct smu_context *smu,
			      struct smu_clock_info *clk_info,
			      enum smu_perf_level_designation designation)
{
	int ret;
	struct smu_performance_level level = {0};

	if (!clk_info)
		return -EINVAL;

	ret = smu_get_perf_level(smu, PERF_LEVEL_ACTIVITY, &level);
	if (ret)
		return -EINVAL;

	clk_info->min_mem_clk = level.memory_clock;
	clk_info->min_eng_clk = level.core_clock;
	clk_info->min_bus_bandwidth = level.non_local_mem_freq * level.non_local_mem_width;

	ret = smu_get_perf_level(smu, designation, &level);
	if (ret)
		return -EINVAL;

	clk_info->min_mem_clk = level.memory_clock;
	clk_info->min_eng_clk = level.core_clock;
	clk_info->min_bus_bandwidth = level.non_local_mem_freq * level.non_local_mem_width;

	return 0;
}