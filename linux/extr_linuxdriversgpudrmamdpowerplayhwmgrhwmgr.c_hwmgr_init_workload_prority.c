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
struct pp_hwmgr {int* workload_prority; size_t* workload_setting; } ;

/* Variables and functions */
 size_t PP_SMC_POWER_PROFILE_COMPUTE ; 
 size_t PP_SMC_POWER_PROFILE_FULLSCREEN3D ; 
 size_t PP_SMC_POWER_PROFILE_POWERSAVING ; 
 size_t PP_SMC_POWER_PROFILE_VIDEO ; 
 size_t PP_SMC_POWER_PROFILE_VR ; 

__attribute__((used)) static void hwmgr_init_workload_prority(struct pp_hwmgr *hwmgr)
{
	hwmgr->workload_prority[PP_SMC_POWER_PROFILE_FULLSCREEN3D] = 2;
	hwmgr->workload_prority[PP_SMC_POWER_PROFILE_POWERSAVING] = 0;
	hwmgr->workload_prority[PP_SMC_POWER_PROFILE_VIDEO] = 1;
	hwmgr->workload_prority[PP_SMC_POWER_PROFILE_VR] = 3;
	hwmgr->workload_prority[PP_SMC_POWER_PROFILE_COMPUTE] = 4;

	hwmgr->workload_setting[0] = PP_SMC_POWER_PROFILE_POWERSAVING;
	hwmgr->workload_setting[1] = PP_SMC_POWER_PROFILE_VIDEO;
	hwmgr->workload_setting[2] = PP_SMC_POWER_PROFILE_FULLSCREEN3D;
	hwmgr->workload_setting[3] = PP_SMC_POWER_PROFILE_VR;
	hwmgr->workload_setting[4] = PP_SMC_POWER_PROFILE_COMPUTE;
}