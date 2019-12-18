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
struct TYPE_3__ {int /*<<< orphan*/ * clocks_table; } ;
struct smu_context {TYPE_1__ smu_table; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
struct TYPE_4__ {int* ClockFrequency; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SmuMetrics_t ;
typedef  int /*<<< orphan*/  DpmClocks_t ;

/* Variables and functions */
 size_t CLOCK_DCFCLK ; 
 size_t CLOCK_FCLK ; 
 size_t CLOCK_GFXCLK ; 
 size_t CLOCK_SOCCLK ; 
 size_t CLOCK_UMCCLK ; 
 int EINVAL ; 
 int /*<<< orphan*/  GET_DPM_CUR_FREQ (int /*<<< orphan*/ *,int,int,int) ; 
 int NUM_DCFCLK_DPM_LEVELS ; 
 int NUM_FCLK_DPM_LEVELS ; 
 int NUM_MEMCLK_DPM_LEVELS ; 
 int NUM_SOCCLK_DPM_LEVELS ; 
 int RENOIR_UMD_PSTATE_GFXCLK ; 
 int SMU_CLK_COUNT ; 
#define  SMU_DCEFCLK 133 
#define  SMU_FCLK 132 
#define  SMU_GFXCLK 131 
#define  SMU_MCLK 130 
#define  SMU_SCLK 129 
#define  SMU_SOCCLK 128 
 int /*<<< orphan*/  SMU_TABLE_SMU_METRICS ; 
 int smu_get_dpm_freq_range (struct smu_context*,int const,int*,int*) ; 
 int smu_update_table (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ sprintf (char*,char*,int,...) ; 

__attribute__((used)) static int renoir_print_clk_levels(struct smu_context *smu,
			enum smu_clk_type clk_type, char *buf)
{
	int i, size = 0, ret = 0;
	uint32_t cur_value = 0, value = 0, count = 0, min = 0, max = 0;
	DpmClocks_t *clk_table = smu->smu_table.clocks_table;
	SmuMetrics_t metrics = {0};

	if (!clk_table || clk_type >= SMU_CLK_COUNT)
		return -EINVAL;

	ret = smu_update_table(smu, SMU_TABLE_SMU_METRICS, 0,
			       (void *)&metrics, false);
	if (ret)
		return ret;

	switch (clk_type) {
	case SMU_GFXCLK:
	case SMU_SCLK:
		/* retirve table returned paramters unit is MHz */
		cur_value = metrics.ClockFrequency[CLOCK_GFXCLK];
		ret = smu_get_dpm_freq_range(smu, SMU_GFXCLK, &min, &max);
		if (!ret) {
			/* driver only know min/max gfx_clk, Add level 1 for all other gfx clks */
			if (cur_value  == max)
				i = 2;
			else if (cur_value == min)
				i = 0;
			else
				i = 1;

			size += sprintf(buf + size, "0: %uMhz %s\n", min,
					i == 0 ? "*" : "");
			size += sprintf(buf + size, "1: %uMhz %s\n",
					i == 1 ? cur_value : RENOIR_UMD_PSTATE_GFXCLK,
					i == 1 ? "*" : "");
			size += sprintf(buf + size, "2: %uMhz %s\n", max,
					i == 2 ? "*" : "");
		}
		return size;
	case SMU_SOCCLK:
		count = NUM_SOCCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_SOCCLK];
		break;
	case SMU_MCLK:
		count = NUM_MEMCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_UMCCLK];
		break;
	case SMU_DCEFCLK:
		count = NUM_DCFCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_DCFCLK];
		break;
	case SMU_FCLK:
		count = NUM_FCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_FCLK];
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		GET_DPM_CUR_FREQ(clk_table, clk_type, i, value);
		size += sprintf(buf + size, "%d: %uMhz %s\n", i, value,
				cur_value == value ? "*" : "");
	}

	return size;
}