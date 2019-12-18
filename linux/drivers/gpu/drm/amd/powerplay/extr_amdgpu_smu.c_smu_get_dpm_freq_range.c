#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int uclk; int gfxclk; int socclk; } ;
struct TYPE_4__ {TYPE_1__ boot_values; } ;
struct smu_context {TYPE_2__ smu_table; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int EINVAL ; 
#define  SMU_GFXCLK 132 
#define  SMU_MCLK 131 
#define  SMU_SCLK 130 
#define  SMU_SOCCLK 129 
#define  SMU_UCLK 128 
 int /*<<< orphan*/  smu_clk_dpm_is_enabled (struct smu_context*,int) ; 
 int smu_get_dpm_ultimate_freq (struct smu_context*,int,int*,int*) ; 

int smu_get_dpm_freq_range(struct smu_context *smu, enum smu_clk_type clk_type,
			   uint32_t *min, uint32_t *max)
{
	uint32_t clock_limit;
	int ret = 0;

	if (!min && !max)
		return -EINVAL;

	if (!smu_clk_dpm_is_enabled(smu, clk_type)) {
		switch (clk_type) {
		case SMU_MCLK:
		case SMU_UCLK:
			clock_limit = smu->smu_table.boot_values.uclk;
			break;
		case SMU_GFXCLK:
		case SMU_SCLK:
			clock_limit = smu->smu_table.boot_values.gfxclk;
			break;
		case SMU_SOCCLK:
			clock_limit = smu->smu_table.boot_values.socclk;
			break;
		default:
			clock_limit = 0;
			break;
		}

		/* clock in Mhz unit */
		if (min)
			*min = clock_limit / 100;
		if (max)
			*max = clock_limit / 100;

		return 0;
	}
	/*
	 * Todo: Use each asic(ASIC_ppt funcs) control the callbacks exposed to the
	 * core driver and then have helpers for stuff that is common(SMU_v11_x | SMU_v12_x funcs).
	 */
	ret = smu_get_dpm_ultimate_freq(smu, clk_type, min, max);
	return ret;
}