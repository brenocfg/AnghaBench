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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL0 ; 
 int /*<<< orphan*/  CG_FDO_CTRL1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  FDO_PWM_MODE_STATIC ; 
 int /*<<< orphan*/  FDO_STATIC_DUTY ; 
 int /*<<< orphan*/  FMAX_DUTY100 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THM ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  mmCG_FDO_CTRL0 ; 
 int /*<<< orphan*/  mmCG_FDO_CTRL1 ; 
 int vega20_fan_ctrl_set_static_mode (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega20_fan_ctrl_stop_smc_fan_control (struct pp_hwmgr*) ; 

int vega20_fan_ctrl_set_fan_speed_percent(struct pp_hwmgr *hwmgr,
		uint32_t speed)
{
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;

	if (speed > 100)
		speed = 100;

	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		vega20_fan_ctrl_stop_smc_fan_control(hwmgr);

	duty100 = REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL1),
				    CG_FDO_CTRL1, FMAX_DUTY100);

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (uint64_t)speed * duty100;
	do_div(tmp64, 100);
	duty = (uint32_t)tmp64;

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL0,
		REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL0),
			CG_FDO_CTRL0, FDO_STATIC_DUTY, duty));

	return vega20_fan_ctrl_set_static_mode(hwmgr, FDO_PWM_MODE_STATIC);
}