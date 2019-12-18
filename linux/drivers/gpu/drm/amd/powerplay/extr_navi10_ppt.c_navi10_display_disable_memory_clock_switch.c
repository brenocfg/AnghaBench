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
struct TYPE_2__ {scalar_t__ max_sustainable_clocks; } ;
struct smu_context {int disable_uclk_switch; int /*<<< orphan*/  hard_min_uclk_req_from_dal; TYPE_1__ smu_table; } ;
struct smu_11_0_max_sustainable_clocks {int /*<<< orphan*/  uclock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_UCLK ; 
 int smu_set_hard_freq_range (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int navi10_display_disable_memory_clock_switch(struct smu_context *smu,
						bool disable_memory_clock_switch)
{
	int ret = 0;
	struct smu_11_0_max_sustainable_clocks *max_sustainable_clocks =
		(struct smu_11_0_max_sustainable_clocks *)
			smu->smu_table.max_sustainable_clocks;
	uint32_t min_memory_clock = smu->hard_min_uclk_req_from_dal;
	uint32_t max_memory_clock = max_sustainable_clocks->uclock;

	if(smu->disable_uclk_switch == disable_memory_clock_switch)
		return 0;

	if(disable_memory_clock_switch)
		ret = smu_set_hard_freq_range(smu, SMU_UCLK, max_memory_clock, 0);
	else
		ret = smu_set_hard_freq_range(smu, SMU_UCLK, min_memory_clock, 0);

	if(!ret)
		smu->disable_uclk_switch = disable_memory_clock_switch;

	return ret;
}