#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
struct TYPE_3__ {int /*<<< orphan*/ * CurrClock; int /*<<< orphan*/  AverageSocclkFrequency; int /*<<< orphan*/  AverageUclkFrequency; int /*<<< orphan*/  AverageGfxclkFrequency; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PPCLK_GFXCLK 130 
#define  PPCLK_SOCCLK 129 
#define  PPCLK_UCLK 128 
 int /*<<< orphan*/  SMU_FEATURE_DPM_GFXCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_SOCCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_UCLK_BIT ; 
 int arcturus_get_metrics_table (struct smu_context*,TYPE_1__*) ; 
 int smu_clk_get_index (struct smu_context*,int) ; 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arcturus_get_current_clk_freq_by_table(struct smu_context *smu,
				       enum smu_clk_type clk_type,
				       uint32_t *value)
{
	static SmuMetrics_t metrics;
	int ret = 0, clk_id = 0;

	if (!value)
		return -EINVAL;

	clk_id = smu_clk_get_index(smu, clk_type);
	if (clk_id < 0)
		return -EINVAL;

	ret = arcturus_get_metrics_table(smu, &metrics);
	if (ret)
		return ret;

	switch (clk_id) {
	case PPCLK_GFXCLK:
		/*
		 * CurrClock[clk_id] can provide accurate
		 *   output only when the dpm feature is enabled.
		 * We can use Average_* for dpm disabled case.
		 *   But this is available for gfxclk/uclk/socclk.
		 */
		if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT))
			*value = metrics.CurrClock[PPCLK_GFXCLK];
		else
			*value = metrics.AverageGfxclkFrequency;
		break;
	case PPCLK_UCLK:
		if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT))
			*value = metrics.CurrClock[PPCLK_UCLK];
		else
			*value = metrics.AverageUclkFrequency;
		break;
	case PPCLK_SOCCLK:
		if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT))
			*value = metrics.CurrClock[PPCLK_SOCCLK];
		else
			*value = metrics.AverageSocclkFrequency;
		break;
	default:
		*value = metrics.CurrClock[clk_id];
		break;
	}

	return ret;
}