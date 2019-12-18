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
struct smu_context {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int SMU_GFXCLK ; 
 int SMU_MCLK ; 
 int SMU_SOCCLK ; 
 int smu_get_dpm_freq_range (struct smu_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int smu_set_soft_freq_range (struct smu_context*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int navi10_unforce_dpm_levels(struct smu_context *smu)
{
	int ret = 0, i = 0;
	uint32_t min_freq, max_freq;
	enum smu_clk_type clk_type;

	enum smu_clk_type clks[] = {
		SMU_GFXCLK,
		SMU_MCLK,
		SMU_SOCCLK,
	};

	for (i = 0; i < ARRAY_SIZE(clks); i++) {
		clk_type = clks[i];
		ret = smu_get_dpm_freq_range(smu, clk_type, &min_freq, &max_freq);
		if (ret)
			return ret;

		ret = smu_set_soft_freq_range(smu, clk_type, min_freq, max_freq);
		if (ret)
			return ret;
	}

	return ret;
}