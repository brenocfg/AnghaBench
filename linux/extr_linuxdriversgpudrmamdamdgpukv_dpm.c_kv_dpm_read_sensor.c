#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u32 ;
struct kv_power_info {TYPE_1__* graphics_level; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  SclkFrequency; } ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GFX_SCLK 129 
#define  AMDGPU_PP_SENSOR_GPU_TEMP 128 
 int EINVAL ; 
 size_t RREG32_SMC (int /*<<< orphan*/ ) ; 
 size_t SMU__NUM_SCLK_DPM_STATE ; 
 size_t TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK ; 
 size_t TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  kv_dpm_get_temp (struct amdgpu_device*) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_dpm_read_sensor(void *handle, int idx,
			      void *value, int *size)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct kv_power_info *pi = kv_get_pi(adev);
	uint32_t sclk;
	u32 pl_index =
		(RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX) &
		TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK) >>
		TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT;

	/* size must be at least 4 bytes for all sensors */
	if (*size < 4)
		return -EINVAL;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GFX_SCLK:
		if (pl_index < SMU__NUM_SCLK_DPM_STATE) {
			sclk = be32_to_cpu(
				pi->graphics_level[pl_index].SclkFrequency);
			*((uint32_t *)value) = sclk;
			*size = 4;
			return 0;
		}
		return -EINVAL;
	case AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uint32_t *)value) = kv_dpm_get_temp(adev);
		*size = 4;
		return 0;
	default:
		return -EINVAL;
	}
}