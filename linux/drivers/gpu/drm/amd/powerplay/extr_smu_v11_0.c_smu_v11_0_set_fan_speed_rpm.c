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
typedef  int uint32_t ;
struct smu_context {int /*<<< orphan*/  mutex; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_TACH_CTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  FDO_PWM_MODE_STATIC_RPM ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PERIOD ; 
 int /*<<< orphan*/  THM ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_asic_get_xclk (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCG_TACH_CTRL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_v11_0_auto_fan_control (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_v11_0_set_fan_static_mode (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_set_fan_speed_rpm(struct smu_context *smu,
				       uint32_t speed)
{
	struct amdgpu_device *adev = smu->adev;
	int ret;
	uint32_t tach_period, crystal_clock_freq;

	if (!speed)
		return -EINVAL;

	mutex_lock(&(smu->mutex));
	ret = smu_v11_0_auto_fan_control(smu, 0);
	if (ret)
		goto set_fan_speed_rpm_failed;

	crystal_clock_freq = amdgpu_asic_get_xclk(adev);
	tach_period = 60 * crystal_clock_freq * 10000 / (8 * speed);
	WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
		     REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
				   CG_TACH_CTRL, TARGET_PERIOD,
				   tach_period));

	ret = smu_v11_0_set_fan_static_mode(smu, FDO_PWM_MODE_STATIC_RPM);

set_fan_speed_rpm_failed:
	mutex_unlock(&(smu->mutex));
	return ret;
}