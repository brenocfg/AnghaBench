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
struct smu_power_gate {int /*<<< orphan*/  vcn_gated; } ;
struct smu_power_context {struct smu_power_gate power_gate; } ;
struct smu_context {int pstate_sclk; int pstate_mclk; struct smu_power_context smu_power; } ;
typedef  enum amd_pp_sensors { ____Placeholder_amd_pp_sensors } amd_pp_sensors ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK 133 
#define  AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK 132 
#define  AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK 131 
#define  AMDGPU_PP_SENSOR_UVD_POWER 130 
#define  AMDGPU_PP_SENSOR_VCE_POWER 129 
#define  AMDGPU_PP_SENSOR_VCN_POWER_STATE 128 
 int EINVAL ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_UVD_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_VCE_BIT ; 
 int smu_feature_get_enabled_mask (struct smu_context*,int*,int) ; 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 

int smu_common_read_sensor(struct smu_context *smu, enum amd_pp_sensors sensor,
			   void *data, uint32_t *size)
{
	struct smu_power_context *smu_power = &smu->smu_power;
	struct smu_power_gate *power_gate = &smu_power->power_gate;
	int ret = 0;

	if(!data || !size)
		return -EINVAL;

	switch (sensor) {
	case AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK:
		*((uint32_t *)data) = smu->pstate_sclk;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK:
		*((uint32_t *)data) = smu->pstate_mclk;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK:
		ret = smu_feature_get_enabled_mask(smu, (uint32_t *)data, 2);
		*size = 8;
		break;
	case AMDGPU_PP_SENSOR_UVD_POWER:
		*(uint32_t *)data = smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UVD_BIT) ? 1 : 0;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_VCE_POWER:
		*(uint32_t *)data = smu_feature_is_enabled(smu, SMU_FEATURE_DPM_VCE_BIT) ? 1 : 0;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_VCN_POWER_STATE:
		*(uint32_t *)data = power_gate->vcn_gated ? 0 : 1;
		*size = 4;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret)
		*size = 0;

	return ret;
}