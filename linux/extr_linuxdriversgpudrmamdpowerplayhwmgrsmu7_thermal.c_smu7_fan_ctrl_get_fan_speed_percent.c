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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ bNoFan; } ;
struct TYPE_4__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_2__ thermal_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_FDO_CTRL1 ; 
 int /*<<< orphan*/  CG_THERMAL_STATUS ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FDO_PWM_DUTY ; 
 int /*<<< orphan*/  FMAX_DUTY100 ; 
 scalar_t__ PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 

int smu7_fan_ctrl_get_fan_speed_percent(struct pp_hwmgr *hwmgr,
		uint32_t *speed)
{
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return -ENODEV;

	duty100 = PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL1, FMAX_DUTY100);
	duty = PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_STATUS, FDO_PWM_DUTY);

	if (duty100 == 0)
		return -EINVAL;


	tmp64 = (uint64_t)duty * 100;
	do_div(tmp64, duty100);
	*speed = (uint32_t)tmp64;

	if (*speed > 100)
		*speed = 100;

	return 0;
}