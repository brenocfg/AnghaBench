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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GFX_MCLK 131 
#define  AMDGPU_PP_SENSOR_GFX_SCLK 130 
#define  AMDGPU_PP_SENSOR_GPU_LOAD 129 
#define  AMDGPU_PP_SENSOR_GPU_TEMP 128 
 int /*<<< orphan*/  AverageGraphicsA ; 
 int EINVAL ; 
 int /*<<< orphan*/  SMU7_SoftRegisters ; 
 int ci_dpm_get_temp (struct amdgpu_device*) ; 
 int ci_get_average_mclk_freq (struct amdgpu_device*) ; 
 int ci_get_average_sclk_freq (struct amdgpu_device*) ; 
 int ci_read_smc_soft_register (struct amdgpu_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_dpm_read_sensor(void *handle, int idx,
			      void *value, int *size)
{
	u32 activity_percent = 50;
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* size must be at least 4 bytes for all sensors */
	if (*size < 4)
		return -EINVAL;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GFX_SCLK:
		*((uint32_t *)value) = ci_get_average_sclk_freq(adev);
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GFX_MCLK:
		*((uint32_t *)value) = ci_get_average_mclk_freq(adev);
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uint32_t *)value) = ci_dpm_get_temp(adev);
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = ci_read_smc_soft_register(adev,
						offsetof(SMU7_SoftRegisters,
							 AverageGraphicsA),
						&activity_percent);
		if (ret == 0) {
			activity_percent += 0x80;
			activity_percent >>= 8;
			activity_percent =
				activity_percent > 100 ? 100 : activity_percent;
		}
		*((uint32_t *)value) = activity_percent;
		*size = 4;
		return 0;
	default:
		return -EINVAL;
	}
}