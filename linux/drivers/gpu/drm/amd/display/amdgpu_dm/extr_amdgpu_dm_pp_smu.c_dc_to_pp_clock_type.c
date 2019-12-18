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
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;

/* Variables and functions */
#define  DM_PP_CLOCK_TYPE_DCEFCLK 136 
#define  DM_PP_CLOCK_TYPE_DCFCLK 135 
#define  DM_PP_CLOCK_TYPE_DISPLAYPHYCLK 134 
#define  DM_PP_CLOCK_TYPE_DISPLAY_CLK 133 
#define  DM_PP_CLOCK_TYPE_DPPCLK 132 
#define  DM_PP_CLOCK_TYPE_ENGINE_CLK 131 
#define  DM_PP_CLOCK_TYPE_FCLK 130 
#define  DM_PP_CLOCK_TYPE_MEMORY_CLK 129 
#define  DM_PP_CLOCK_TYPE_PIXELCLK 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int amd_pp_dcef_clock ; 
 int amd_pp_dcf_clock ; 
 int amd_pp_disp_clock ; 
 int amd_pp_dpp_clock ; 
 int amd_pp_f_clock ; 
 int amd_pp_mem_clock ; 
 int amd_pp_phy_clock ; 
 int amd_pp_pixel_clock ; 
 int amd_pp_sys_clock ; 

__attribute__((used)) static enum amd_pp_clock_type dc_to_pp_clock_type(
		enum dm_pp_clock_type dm_pp_clk_type)
{
	enum amd_pp_clock_type amd_pp_clk_type = 0;

	switch (dm_pp_clk_type) {
	case DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		amd_pp_clk_type = amd_pp_disp_clock;
		break;
	case DM_PP_CLOCK_TYPE_ENGINE_CLK:
		amd_pp_clk_type = amd_pp_sys_clock;
		break;
	case DM_PP_CLOCK_TYPE_MEMORY_CLK:
		amd_pp_clk_type = amd_pp_mem_clock;
		break;
	case DM_PP_CLOCK_TYPE_DCEFCLK:
		amd_pp_clk_type  = amd_pp_dcef_clock;
		break;
	case DM_PP_CLOCK_TYPE_DCFCLK:
		amd_pp_clk_type = amd_pp_dcf_clock;
		break;
	case DM_PP_CLOCK_TYPE_PIXELCLK:
		amd_pp_clk_type = amd_pp_pixel_clock;
		break;
	case DM_PP_CLOCK_TYPE_FCLK:
		amd_pp_clk_type = amd_pp_f_clock;
		break;
	case DM_PP_CLOCK_TYPE_DISPLAYPHYCLK:
		amd_pp_clk_type = amd_pp_phy_clock;
		break;
	case DM_PP_CLOCK_TYPE_DPPCLK:
		amd_pp_clk_type = amd_pp_dpp_clock;
		break;
	default:
		DRM_ERROR("DM_PPLIB: invalid clock type: %d!\n",
				dm_pp_clk_type);
		break;
	}

	return amd_pp_clk_type;
}