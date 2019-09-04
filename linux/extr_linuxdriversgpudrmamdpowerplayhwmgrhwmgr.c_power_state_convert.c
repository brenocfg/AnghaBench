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
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;
typedef  enum PP_StateUILabel { ____Placeholder_PP_StateUILabel } PP_StateUILabel ;

/* Variables and functions */
#define  POWER_STATE_TYPE_BALANCED 130 
#define  POWER_STATE_TYPE_BATTERY 129 
#define  POWER_STATE_TYPE_PERFORMANCE 128 
 int PP_StateUILabel_Balanced ; 
 int PP_StateUILabel_Battery ; 
 int PP_StateUILabel_None ; 
 int PP_StateUILabel_Performance ; 

__attribute__((used)) static enum PP_StateUILabel power_state_convert(enum amd_pm_state_type  state)
{
	switch (state) {
	case POWER_STATE_TYPE_BATTERY:
		return PP_StateUILabel_Battery;
	case POWER_STATE_TYPE_BALANCED:
		return PP_StateUILabel_Balanced;
	case POWER_STATE_TYPE_PERFORMANCE:
		return PP_StateUILabel_Performance;
	default:
		return PP_StateUILabel_None;
	}
}