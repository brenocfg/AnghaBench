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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int dummy; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetSclkSoftMax ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSclkSoftMin ; 
#define  PP_SCLK 128 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_force_clock_level(struct pp_hwmgr *hwmgr,
		enum pp_clock_type type, uint32_t mask)
{
	switch (type) {
	case PP_SCLK:
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMin,
				mask);
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSclkSoftMax,
				mask);
		break;
	default:
		break;
	}

	return 0;
}