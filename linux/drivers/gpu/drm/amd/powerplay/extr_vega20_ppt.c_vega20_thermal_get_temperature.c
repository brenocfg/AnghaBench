#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amd_pp_sensors { ____Placeholder_amd_pp_sensors } amd_pp_sensors ;
struct TYPE_3__ {int TemperatureEdge; int TemperatureHBM; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_EDGE_TEMP 130 
#define  AMDGPU_PP_SENSOR_HOTSPOT_TEMP 129 
#define  AMDGPU_PP_SENSOR_MEM_TEMP 128 
 int CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK ; 
 int CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT ; 
 int EINVAL ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMU_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int /*<<< orphan*/  THM ; 
 int /*<<< orphan*/  mmCG_MULT_THERMAL_STATUS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int vega20_get_metrics_table (struct smu_context*,TYPE_1__*) ; 

__attribute__((used)) static int vega20_thermal_get_temperature(struct smu_context *smu,
					     enum amd_pp_sensors sensor,
					     uint32_t *value)
{
	struct amdgpu_device *adev = smu->adev;
	SmuMetrics_t metrics;
	uint32_t temp = 0;
	int ret = 0;

	if (!value)
		return -EINVAL;

	ret = vega20_get_metrics_table(smu, &metrics);
	if (ret)
		return ret;

	switch (sensor) {
	case AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		temp = RREG32_SOC15(THM, 0, mmCG_MULT_THERMAL_STATUS);
		temp = (temp & CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK) >>
				CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT;

		temp = temp & 0x1ff;
		temp *= SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;

		*value = temp;
		break;
	case AMDGPU_PP_SENSOR_EDGE_TEMP:
		*value = metrics.TemperatureEdge *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		break;
	case AMDGPU_PP_SENSOR_MEM_TEMP:
		*value = metrics.TemperatureHBM *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		break;
	default:
		pr_err("Invalid sensor for retrieving temp\n");
		return -EINVAL;
	}

	return 0;
}