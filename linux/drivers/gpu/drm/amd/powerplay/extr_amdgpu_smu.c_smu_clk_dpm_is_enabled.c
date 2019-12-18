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
struct smu_context {int dummy; } ;
typedef  enum smu_feature_mask { ____Placeholder_smu_feature_mask } smu_feature_mask ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int SMU_FEATURE_DPM_GFXCLK_BIT ; 
 int SMU_FEATURE_DPM_SOCCLK_BIT ; 
 int SMU_FEATURE_DPM_UCLK_BIT ; 
#define  SMU_GFXCLK 132 
#define  SMU_MCLK 131 
#define  SMU_SCLK 130 
#define  SMU_SOCCLK 129 
#define  SMU_UCLK 128 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int) ; 

bool smu_clk_dpm_is_enabled(struct smu_context *smu, enum smu_clk_type clk_type)
{
	enum smu_feature_mask feature_id = 0;

	switch (clk_type) {
	case SMU_MCLK:
	case SMU_UCLK:
		feature_id = SMU_FEATURE_DPM_UCLK_BIT;
		break;
	case SMU_GFXCLK:
	case SMU_SCLK:
		feature_id = SMU_FEATURE_DPM_GFXCLK_BIT;
		break;
	case SMU_SOCCLK:
		feature_id = SMU_FEATURE_DPM_SOCCLK_BIT;
		break;
	default:
		return true;
	}

	if(!smu_feature_is_enabled(smu, feature_id)) {
		return false;
	}

	return true;
}