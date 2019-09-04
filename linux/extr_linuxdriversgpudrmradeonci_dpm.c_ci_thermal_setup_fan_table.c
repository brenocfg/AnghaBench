#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int ucode_fan_control; int pwm_min; int t_med; int t_min; int t_high; int pwm_med; int pwm_high; int t_max; int t_hyst; int cycle_delay; } ;
struct TYPE_6__ {TYPE_1__ fan; } ;
struct TYPE_7__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct ci_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  fan_table_start; } ;
typedef  int /*<<< orphan*/  fan_table ;
struct TYPE_8__ {scalar_t__ TempSrc; void* FdoMax; int /*<<< orphan*/  RefreshPeriod; void* TempRespLim; void* HystSlope; void* HystUp; void* HystDown; void* FdoMin; void* Slope2; void* Slope1; void* TempMax; void* TempMed; void* TempMin; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ SMU7_Discrete_FanTable ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL1 ; 
 int /*<<< orphan*/  CG_MULT_THERMAL_CTRL ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FDO_MODE_HARDWARE ; 
 int FMAX_DUTY100_MASK ; 
 int FMAX_DUTY100_SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int TEMP_SEL_MASK ; 
 int TEMP_SEL_SHIFT ; 
 int ci_copy_bytes_to_smc (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int radeon_get_xclk (struct radeon_device*) ; 

__attribute__((used)) static int ci_thermal_setup_fan_table(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	SMU7_Discrete_FanTable fan_table = { FDO_MODE_HARDWARE };
	u32 duty100;
	u32 t_diff1, t_diff2, pwm_diff1, pwm_diff2;
	u16 fdo_min, slope1, slope2;
	u32 reference_clock, tmp;
	int ret;
	u64 tmp64;

	if (!pi->fan_table_start) {
		rdev->pm.dpm.fan.ucode_fan_control = false;
		return 0;
	}

	duty100 = (RREG32_SMC(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;

	if (duty100 == 0) {
		rdev->pm.dpm.fan.ucode_fan_control = false;
		return 0;
	}

	tmp64 = (u64)rdev->pm.dpm.fan.pwm_min * duty100;
	do_div(tmp64, 10000);
	fdo_min = (u16)tmp64;

	t_diff1 = rdev->pm.dpm.fan.t_med - rdev->pm.dpm.fan.t_min;
	t_diff2 = rdev->pm.dpm.fan.t_high - rdev->pm.dpm.fan.t_med;

	pwm_diff1 = rdev->pm.dpm.fan.pwm_med - rdev->pm.dpm.fan.pwm_min;
	pwm_diff2 = rdev->pm.dpm.fan.pwm_high - rdev->pm.dpm.fan.pwm_med;

	slope1 = (u16)((50 + ((16 * duty100 * pwm_diff1) / t_diff1)) / 100);
	slope2 = (u16)((50 + ((16 * duty100 * pwm_diff2) / t_diff2)) / 100);

	fan_table.TempMin = cpu_to_be16((50 + rdev->pm.dpm.fan.t_min) / 100);
	fan_table.TempMed = cpu_to_be16((50 + rdev->pm.dpm.fan.t_med) / 100);
	fan_table.TempMax = cpu_to_be16((50 + rdev->pm.dpm.fan.t_max) / 100);

	fan_table.Slope1 = cpu_to_be16(slope1);
	fan_table.Slope2 = cpu_to_be16(slope2);

	fan_table.FdoMin = cpu_to_be16(fdo_min);

	fan_table.HystDown = cpu_to_be16(rdev->pm.dpm.fan.t_hyst);

	fan_table.HystUp = cpu_to_be16(1);

	fan_table.HystSlope = cpu_to_be16(1);

	fan_table.TempRespLim = cpu_to_be16(5);

	reference_clock = radeon_get_xclk(rdev);

	fan_table.RefreshPeriod = cpu_to_be32((rdev->pm.dpm.fan.cycle_delay *
					       reference_clock) / 1600);

	fan_table.FdoMax = cpu_to_be16((u16)duty100);

	tmp = (RREG32_SMC(CG_MULT_THERMAL_CTRL) & TEMP_SEL_MASK) >> TEMP_SEL_SHIFT;
	fan_table.TempSrc = (uint8_t)tmp;

	ret = ci_copy_bytes_to_smc(rdev,
				   pi->fan_table_start,
				   (u8 *)(&fan_table),
				   sizeof(fan_table),
				   pi->sram_end);

	if (ret) {
		DRM_ERROR("Failed to load fan table to the SMC.");
		rdev->pm.dpm.fan.ucode_fan_control = false;
	}

	return 0;
}