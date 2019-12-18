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
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;

/* Variables and functions */
#define  DM_PP_CLOCK_TYPE_DCEFCLK 132 
#define  DM_PP_CLOCK_TYPE_DISPLAY_CLK 131 
#define  DM_PP_CLOCK_TYPE_ENGINE_CLK 130 
#define  DM_PP_CLOCK_TYPE_MEMORY_CLK 129 
#define  DM_PP_CLOCK_TYPE_SOCCLK 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int SMU_CLK_COUNT ; 
 int SMU_DCEFCLK ; 
 int SMU_DISPCLK ; 
 int SMU_GFXCLK ; 
 int SMU_MCLK ; 
 int SMU_SOCCLK ; 

__attribute__((used)) static enum smu_clk_type dc_to_smu_clock_type(
		enum dm_pp_clock_type dm_pp_clk_type)
{
	enum smu_clk_type smu_clk_type = SMU_CLK_COUNT;

	switch (dm_pp_clk_type) {
	case DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		smu_clk_type = SMU_DISPCLK;
		break;
	case DM_PP_CLOCK_TYPE_ENGINE_CLK:
		smu_clk_type = SMU_GFXCLK;
		break;
	case DM_PP_CLOCK_TYPE_MEMORY_CLK:
		smu_clk_type = SMU_MCLK;
		break;
	case DM_PP_CLOCK_TYPE_DCEFCLK:
		smu_clk_type = SMU_DCEFCLK;
		break;
	case DM_PP_CLOCK_TYPE_SOCCLK:
		smu_clk_type = SMU_SOCCLK;
		break;
	default:
		DRM_ERROR("DM_PPLIB: invalid clock type: %d!\n",
			  dm_pp_clk_type);
		break;
	}

	return smu_clk_type;
}