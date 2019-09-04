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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  usMaxFanRPM; } ;
struct TYPE_4__ {TYPE_1__ advanceFanControlParameters; } ;
struct pp_hwmgr {TYPE_2__ thermal_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetFanRpmMax ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_set_max_fan_rpm_output(struct pp_hwmgr *hwmgr, uint16_t us_max_fan_rpm)
{
	hwmgr->thermal_controller.
	advanceFanControlParameters.usMaxFanRPM = us_max_fan_rpm;

	return smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetFanRpmMax, us_max_fan_rpm);
}