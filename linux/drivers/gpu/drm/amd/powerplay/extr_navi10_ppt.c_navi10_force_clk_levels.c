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
typedef  scalar_t__ uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
#define  SMU_DCEFCLK 134 
#define  SMU_FCLK 133 
#define  SMU_GFXCLK 132 
#define  SMU_MCLK 131 
#define  SMU_SCLK 130 
#define  SMU_SOCCLK 129 
#define  SMU_UCLK 128 
 scalar_t__ ffs (scalar_t__) ; 
 scalar_t__ fls (scalar_t__) ; 
 int smu_get_dpm_freq_by_index (struct smu_context*,int,scalar_t__,scalar_t__*) ; 
 int smu_set_soft_freq_range (struct smu_context*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int navi10_force_clk_levels(struct smu_context *smu,
				   enum smu_clk_type clk_type, uint32_t mask)
{

	int ret = 0, size = 0;
	uint32_t soft_min_level = 0, soft_max_level = 0, min_freq = 0, max_freq = 0;

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	switch (clk_type) {
	case SMU_GFXCLK:
	case SMU_SCLK:
	case SMU_SOCCLK:
	case SMU_MCLK:
	case SMU_UCLK:
	case SMU_DCEFCLK:
	case SMU_FCLK:
		ret = smu_get_dpm_freq_by_index(smu, clk_type, soft_min_level, &min_freq);
		if (ret)
			return size;

		ret = smu_get_dpm_freq_by_index(smu, clk_type, soft_max_level, &max_freq);
		if (ret)
			return size;

		ret = smu_set_soft_freq_range(smu, clk_type, min_freq, max_freq);
		if (ret)
			return size;
		break;
	default:
		break;
	}

	return size;
}