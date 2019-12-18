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
typedef  enum dm_pp_clocks_state { ____Placeholder_dm_pp_clocks_state } dm_pp_clocks_state ;
typedef  enum PP_DAL_POWERLEVEL { ____Placeholder_PP_DAL_POWERLEVEL } PP_DAL_POWERLEVEL ;

/* Variables and functions */
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_0 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_1 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_2 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_3 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_4 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_5 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_6 ; 
 int DM_PP_CLOCKS_DPM_STATE_LEVEL_7 ; 
 int DM_PP_CLOCKS_STATE_INVALID ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  PP_DAL_POWERLEVEL_0 135 
#define  PP_DAL_POWERLEVEL_1 134 
#define  PP_DAL_POWERLEVEL_2 133 
#define  PP_DAL_POWERLEVEL_3 132 
#define  PP_DAL_POWERLEVEL_4 131 
#define  PP_DAL_POWERLEVEL_5 130 
#define  PP_DAL_POWERLEVEL_6 129 
#define  PP_DAL_POWERLEVEL_7 128 

__attribute__((used)) static enum dm_pp_clocks_state pp_to_dc_powerlevel_state(
			enum PP_DAL_POWERLEVEL max_clocks_state)
{
	switch (max_clocks_state) {
	case PP_DAL_POWERLEVEL_0:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_0;
	case PP_DAL_POWERLEVEL_1:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_1;
	case PP_DAL_POWERLEVEL_2:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_2;
	case PP_DAL_POWERLEVEL_3:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_3;
	case PP_DAL_POWERLEVEL_4:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_4;
	case PP_DAL_POWERLEVEL_5:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_5;
	case PP_DAL_POWERLEVEL_6:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_6;
	case PP_DAL_POWERLEVEL_7:
		return DM_PP_CLOCKS_DPM_STATE_LEVEL_7;
	default:
		DRM_ERROR("DM_PPLIB: invalid powerlevel state: %d!\n",
				max_clocks_state);
		return DM_PP_CLOCKS_STATE_INVALID;
	}
}