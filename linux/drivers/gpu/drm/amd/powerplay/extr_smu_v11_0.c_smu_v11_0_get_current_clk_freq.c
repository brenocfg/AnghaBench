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
typedef  int uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int EINVAL ; 
 int SMU_CLK_COUNT ; 
 int /*<<< orphan*/  SMU_MSG_GetDpmClockFreq ; 
 int smu_clk_get_index (struct smu_context*,int) ; 
 int smu_get_current_clk_freq_by_table (struct smu_context*,int,int*) ; 
 scalar_t__ smu_msg_get_index (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_read_smc_arg (struct smu_context*,int*) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_v11_0_get_current_clk_freq(struct smu_context *smu,
					  enum smu_clk_type clk_id,
					  uint32_t *value)
{
	int ret = 0;
	uint32_t freq = 0;
	int asic_clk_id;

	if (clk_id >= SMU_CLK_COUNT || !value)
		return -EINVAL;

	asic_clk_id = smu_clk_get_index(smu, clk_id);
	if (asic_clk_id < 0)
		return -EINVAL;

	/* if don't has GetDpmClockFreq Message, try get current clock by SmuMetrics_t */
	if (smu_msg_get_index(smu, SMU_MSG_GetDpmClockFreq) < 0)
		ret =  smu_get_current_clk_freq_by_table(smu, clk_id, &freq);
	else {
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_GetDpmClockFreq,
						  (asic_clk_id << 16));
		if (ret)
			return ret;

		ret = smu_read_smc_arg(smu, &freq);
		if (ret)
			return ret;
	}

	freq *= 100;
	*value = freq;

	return ret;
}