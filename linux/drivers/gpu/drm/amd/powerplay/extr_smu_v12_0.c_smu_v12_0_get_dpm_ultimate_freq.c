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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_context {int /*<<< orphan*/  mutex; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int EINVAL ; 
#define  SMU_GFXCLK 130 
 int /*<<< orphan*/  SMU_MSG_GetMaxGfxclkFrequency ; 
 int /*<<< orphan*/  SMU_MSG_GetMinGfxclkFrequency ; 
#define  SMU_SCLK 129 
#define  SMU_UCLK 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_get_dpm_uclk_limited (struct smu_context*,int /*<<< orphan*/ *,int) ; 
 int smu_read_smc_arg (struct smu_context*,int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v12_0_get_dpm_ultimate_freq(struct smu_context *smu, enum smu_clk_type clk_type,
						 uint32_t *min, uint32_t *max)
{
	int ret = 0;

	mutex_lock(&smu->mutex);

	if (max) {
		switch (clk_type) {
		case SMU_GFXCLK:
		case SMU_SCLK:
			ret = smu_send_smc_msg(smu, SMU_MSG_GetMaxGfxclkFrequency);
			if (ret) {
				pr_err("Attempt to get max GX frequency from SMC Failed !\n");
				goto failed;
			}
			ret = smu_read_smc_arg(smu, max);
			if (ret)
				goto failed;
			break;
		case SMU_UCLK:
			ret = smu_get_dpm_uclk_limited(smu, max, true);
			if (ret)
				goto failed;
			break;
		default:
			ret = -EINVAL;
			goto failed;

		}
	}

	if (min) {
		switch (clk_type) {
		case SMU_GFXCLK:
		case SMU_SCLK:
			ret = smu_send_smc_msg(smu, SMU_MSG_GetMinGfxclkFrequency);
			if (ret) {
				pr_err("Attempt to get min GX frequency from SMC Failed !\n");
				goto failed;
			}
			ret = smu_read_smc_arg(smu, min);
			if (ret)
				goto failed;
			break;
		case SMU_UCLK:
			ret = smu_get_dpm_uclk_limited(smu, min, false);
			if (ret)
				goto failed;
			break;
		default:
			ret = -EINVAL;
			goto failed;
		}

	}
failed:
	mutex_unlock(&smu->mutex);
	return ret;
}