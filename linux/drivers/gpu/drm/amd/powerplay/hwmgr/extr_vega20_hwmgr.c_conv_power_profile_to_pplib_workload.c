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

/* Variables and functions */
#define  PP_SMC_POWER_PROFILE_BOOTUP_DEFAULT 134 
#define  PP_SMC_POWER_PROFILE_COMPUTE 133 
#define  PP_SMC_POWER_PROFILE_CUSTOM 132 
#define  PP_SMC_POWER_PROFILE_FULLSCREEN3D 131 
#define  PP_SMC_POWER_PROFILE_POWERSAVING 130 
#define  PP_SMC_POWER_PROFILE_VIDEO 129 
#define  PP_SMC_POWER_PROFILE_VR 128 
 int WORKLOAD_DEFAULT_BIT ; 
 int WORKLOAD_PPLIB_COMPUTE_BIT ; 
 int WORKLOAD_PPLIB_CUSTOM_BIT ; 
 int WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT ; 
 int WORKLOAD_PPLIB_POWER_SAVING_BIT ; 
 int WORKLOAD_PPLIB_VIDEO_BIT ; 
 int WORKLOAD_PPLIB_VR_BIT ; 

__attribute__((used)) static int conv_power_profile_to_pplib_workload(int power_profile)
{
	int pplib_workload = 0;

	switch (power_profile) {
	case PP_SMC_POWER_PROFILE_BOOTUP_DEFAULT:
		pplib_workload = WORKLOAD_DEFAULT_BIT;
		break;
	case PP_SMC_POWER_PROFILE_FULLSCREEN3D:
		pplib_workload = WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT;
		break;
	case PP_SMC_POWER_PROFILE_POWERSAVING:
		pplib_workload = WORKLOAD_PPLIB_POWER_SAVING_BIT;
		break;
	case PP_SMC_POWER_PROFILE_VIDEO:
		pplib_workload = WORKLOAD_PPLIB_VIDEO_BIT;
		break;
	case PP_SMC_POWER_PROFILE_VR:
		pplib_workload = WORKLOAD_PPLIB_VR_BIT;
		break;
	case PP_SMC_POWER_PROFILE_COMPUTE:
		pplib_workload = WORKLOAD_PPLIB_COMPUTE_BIT;
		break;
	case PP_SMC_POWER_PROFILE_CUSTOM:
		pplib_workload = WORKLOAD_PPLIB_CUSTOM_BIT;
		break;
	}

	return pplib_workload;
}