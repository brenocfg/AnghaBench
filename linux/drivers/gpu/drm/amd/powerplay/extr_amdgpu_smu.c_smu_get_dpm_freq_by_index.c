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
typedef  int uint16_t ;
struct smu_context {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SMU_MSG_GetDpmFreqByIndex ; 
 int /*<<< orphan*/  smu_clk_dpm_is_enabled (struct smu_context*,int) ; 
 int smu_clk_get_index (struct smu_context*,int) ; 
 int smu_read_smc_arg (struct smu_context*,int*) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

int smu_get_dpm_freq_by_index(struct smu_context *smu, enum smu_clk_type clk_type,
			      uint16_t level, uint32_t *value)
{
	int ret = 0, clk_id = 0;
	uint32_t param;

	if (!value)
		return -EINVAL;

	if (!smu_clk_dpm_is_enabled(smu, clk_type))
		return 0;

	clk_id = smu_clk_get_index(smu, clk_type);
	if (clk_id < 0)
		return clk_id;

	param = (uint32_t)(((clk_id & 0xffff) << 16) | (level & 0xffff));

	ret = smu_send_smc_msg_with_param(smu,SMU_MSG_GetDpmFreqByIndex,
					  param);
	if (ret)
		return ret;

	ret = smu_read_smc_arg(smu, &param);
	if (ret)
		return ret;

	/* BIT31:  0 - Fine grained DPM, 1 - Dicrete DPM
	 * now, we un-support it */
	*value = param & 0x7fffffff;

	return ret;
}