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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct vega12_hwmgr {int /*<<< orphan*/  vce_power_gated; int /*<<< orphan*/  uvd_power_gated; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_3__ {int TemperatureHotspot; int TemperatureHBM; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK 138 
#define  AMDGPU_PP_SENSOR_GFX_MCLK 137 
#define  AMDGPU_PP_SENSOR_GFX_SCLK 136 
#define  AMDGPU_PP_SENSOR_GPU_LOAD 135 
#define  AMDGPU_PP_SENSOR_GPU_POWER 134 
#define  AMDGPU_PP_SENSOR_GPU_TEMP 133 
#define  AMDGPU_PP_SENSOR_HOTSPOT_TEMP 132 
#define  AMDGPU_PP_SENSOR_MEM_LOAD 131 
#define  AMDGPU_PP_SENSOR_MEM_TEMP 130 
#define  AMDGPU_PP_SENSOR_UVD_POWER 129 
#define  AMDGPU_PP_SENSOR_VCE_POWER 128 
 int EINVAL ; 
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int vega12_get_current_activity_percent (struct pp_hwmgr*,int,int*) ; 
 int vega12_get_current_gfx_clk_freq (struct pp_hwmgr*,int*) ; 
 int vega12_get_current_mclk_freq (struct pp_hwmgr*,int*) ; 
 int vega12_get_enabled_smc_features (struct pp_hwmgr*,int /*<<< orphan*/ *) ; 
 int vega12_get_gpu_power (struct pp_hwmgr*,int*) ; 
 int vega12_get_metrics_table (struct pp_hwmgr*,TYPE_1__*) ; 
 int vega12_thermal_get_temperature (struct pp_hwmgr*) ; 

__attribute__((used)) static int vega12_read_sensor(struct pp_hwmgr *hwmgr, int idx,
			      void *value, int *size)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);
	SmuMetrics_t metrics_table;
	int ret = 0;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = vega12_get_current_gfx_clk_freq(hwmgr, (uint32_t *)value);
		if (!ret)
			*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = vega12_get_current_mclk_freq(hwmgr, (uint32_t *)value);
		if (!ret)
			*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GPU_LOAD:
	case AMDGPU_PP_SENSOR_MEM_LOAD:
		ret = vega12_get_current_activity_percent(hwmgr, idx, (uint32_t *)value);
		if (!ret)
			*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uint32_t *)value) = vega12_thermal_get_temperature(hwmgr);
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = vega12_get_metrics_table(hwmgr, &metrics_table);
		if (ret)
			return ret;

		*((uint32_t *)value) = metrics_table.TemperatureHotspot *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = vega12_get_metrics_table(hwmgr, &metrics_table);
		if (ret)
			return ret;

		*((uint32_t *)value) = metrics_table.TemperatureHBM *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_UVD_POWER:
		*((uint32_t *)value) = data->uvd_power_gated ? 0 : 1;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_VCE_POWER:
		*((uint32_t *)value) = data->vce_power_gated ? 0 : 1;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GPU_POWER:
		ret = vega12_get_gpu_power(hwmgr, (uint32_t *)value);
		if (!ret)
			*size = 4;
		break;
	case AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK:
		ret = vega12_get_enabled_smc_features(hwmgr, (uint64_t *)value);
		if (!ret)
			*size = 8;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}