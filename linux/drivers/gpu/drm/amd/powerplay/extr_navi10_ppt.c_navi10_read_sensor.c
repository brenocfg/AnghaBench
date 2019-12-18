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
typedef  int uint32_t ;
struct smu_table_context {TYPE_1__* driver_pptable; } ;
struct smu_context {int /*<<< orphan*/  sensor_lock; struct smu_table_context smu_table; } ;
typedef  enum amd_pp_sensors { ____Placeholder_amd_pp_sensors } amd_pp_sensors ;
struct TYPE_2__ {int FanMaximumRpm; } ;
typedef  TYPE_1__ PPTable_t ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_EDGE_TEMP 134 
#define  AMDGPU_PP_SENSOR_GPU_LOAD 133 
#define  AMDGPU_PP_SENSOR_GPU_POWER 132 
#define  AMDGPU_PP_SENSOR_HOTSPOT_TEMP 131 
#define  AMDGPU_PP_SENSOR_MAX_FAN_RPM 130 
#define  AMDGPU_PP_SENSOR_MEM_LOAD 129 
#define  AMDGPU_PP_SENSOR_MEM_TEMP 128 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int navi10_get_current_activity_percent (struct smu_context*,int,int*) ; 
 int navi10_get_gpu_power (struct smu_context*,int*) ; 
 int navi10_thermal_get_temperature (struct smu_context*,int,int*) ; 
 int smu_smc_read_sensor (struct smu_context*,int,void*,int*) ; 

__attribute__((used)) static int navi10_read_sensor(struct smu_context *smu,
				 enum amd_pp_sensors sensor,
				 void *data, uint32_t *size)
{
	int ret = 0;
	struct smu_table_context *table_context = &smu->smu_table;
	PPTable_t *pptable = table_context->driver_pptable;

	if(!data || !size)
		return -EINVAL;

	mutex_lock(&smu->sensor_lock);
	switch (sensor) {
	case AMDGPU_PP_SENSOR_MAX_FAN_RPM:
		*(uint32_t *)data = pptable->FanMaximumRpm;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_MEM_LOAD:
	case AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = navi10_get_current_activity_percent(smu, sensor, (uint32_t *)data);
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GPU_POWER:
		ret = navi10_get_gpu_power(smu, (uint32_t *)data);
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
	case AMDGPU_PP_SENSOR_EDGE_TEMP:
	case AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = navi10_thermal_get_temperature(smu, sensor, (uint32_t *)data);
		*size = 4;
		break;
	default:
		ret = smu_smc_read_sensor(smu, sensor, data, size);
	}
	mutex_unlock(&smu->sensor_lock);

	return ret;
}