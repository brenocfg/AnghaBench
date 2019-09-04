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
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
typedef  size_t u16 ;
struct smu8_hwmgr {int /*<<< orphan*/  vce_power_gated; int /*<<< orphan*/  uvd_power_gated; } ;
struct TYPE_5__ {struct phm_uvd_clock_voltage_dependency_table* uvd_clock_voltage_dependency_table; struct phm_vce_clock_voltage_dependency_table* vce_clock_voltage_dependency_table; struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_1__ dyn_state; struct smu8_hwmgr* backend; } ;
struct phm_vce_clock_voltage_dependency_table {TYPE_4__* entries; } ;
struct phm_uvd_clock_voltage_dependency_table {TYPE_3__* entries; } ;
struct phm_clock_voltage_dependency_table {TYPE_2__* entries; } ;
struct TYPE_8__ {size_t ecclk; } ;
struct TYPE_7__ {size_t vclk; size_t dclk; } ;
struct TYPE_6__ {size_t clk; } ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GFX_SCLK 137 
#define  AMDGPU_PP_SENSOR_GPU_LOAD 136 
#define  AMDGPU_PP_SENSOR_GPU_TEMP 135 
#define  AMDGPU_PP_SENSOR_UVD_DCLK 134 
#define  AMDGPU_PP_SENSOR_UVD_POWER 133 
#define  AMDGPU_PP_SENSOR_UVD_VCLK 132 
#define  AMDGPU_PP_SENSOR_VCE_ECCLK 131 
#define  AMDGPU_PP_SENSOR_VCE_POWER 130 
#define  AMDGPU_PP_SENSOR_VDDGFX 129 
#define  AMDGPU_PP_SENSOR_VDDNB 128 
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 size_t CURRENT_GFX_VID_MASK ; 
 size_t CURRENT_GFX_VID__SHIFT ; 
 size_t CURRENT_NB_VID_MASK ; 
 size_t CURRENT_NB_VID__SHIFT ; 
 int /*<<< orphan*/  CURR_SCLK_INDEX ; 
 int /*<<< orphan*/  CURR_UVD_INDEX ; 
 int /*<<< orphan*/  CURR_VCE_INDEX ; 
 int EINVAL ; 
 size_t NUM_SCLK_LEVELS ; 
 size_t PHM_GET_FIELD (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPSMC_MSG_GetAverageGraphicsActivity ; 
 size_t SMU8_MAX_HARDWARE_POWERLEVELS ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX_2 ; 
 size_t cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSMUSVI_GFX_CURRENTVID ; 
 int /*<<< orphan*/  ixSMUSVI_NB_CURRENTVID ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX_2 ; 
 int /*<<< orphan*/  mmSMU_MP1_SRBM2P_ARG_0 ; 
 int smu8_convert_8Bit_index_to_voltage (struct pp_hwmgr*,size_t) ; 
 size_t smu8_thermal_get_temperature (struct pp_hwmgr*) ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_read_sensor(struct pp_hwmgr *hwmgr, int idx,
			  void *value, int *size)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	struct phm_clock_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;

	struct phm_vce_clock_voltage_dependency_table *vce_table =
		hwmgr->dyn_state.vce_clock_voltage_dependency_table;

	struct phm_uvd_clock_voltage_dependency_table *uvd_table =
		hwmgr->dyn_state.uvd_clock_voltage_dependency_table;

	uint32_t sclk_index = PHM_GET_FIELD(cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixTARGET_AND_CURRENT_PROFILE_INDEX),
					TARGET_AND_CURRENT_PROFILE_INDEX, CURR_SCLK_INDEX);
	uint32_t uvd_index = PHM_GET_FIELD(cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixTARGET_AND_CURRENT_PROFILE_INDEX_2),
					TARGET_AND_CURRENT_PROFILE_INDEX_2, CURR_UVD_INDEX);
	uint32_t vce_index = PHM_GET_FIELD(cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixTARGET_AND_CURRENT_PROFILE_INDEX_2),
					TARGET_AND_CURRENT_PROFILE_INDEX_2, CURR_VCE_INDEX);

	uint32_t sclk, vclk, dclk, ecclk, tmp, activity_percent;
	uint16_t vddnb, vddgfx;
	int result;

	/* size must be at least 4 bytes for all sensors */
	if (*size < 4)
		return -EINVAL;
	*size = 4;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GFX_SCLK:
		if (sclk_index < NUM_SCLK_LEVELS) {
			sclk = table->entries[sclk_index].clk;
			*((uint32_t *)value) = sclk;
			return 0;
		}
		return -EINVAL;
	case AMDGPU_PP_SENSOR_VDDNB:
		tmp = (cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixSMUSVI_NB_CURRENTVID) &
			CURRENT_NB_VID_MASK) >> CURRENT_NB_VID__SHIFT;
		vddnb = smu8_convert_8Bit_index_to_voltage(hwmgr, tmp) / 4;
		*((uint32_t *)value) = vddnb;
		return 0;
	case AMDGPU_PP_SENSOR_VDDGFX:
		tmp = (cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixSMUSVI_GFX_CURRENTVID) &
			CURRENT_GFX_VID_MASK) >> CURRENT_GFX_VID__SHIFT;
		vddgfx = smu8_convert_8Bit_index_to_voltage(hwmgr, (u16)tmp) / 4;
		*((uint32_t *)value) = vddgfx;
		return 0;
	case AMDGPU_PP_SENSOR_UVD_VCLK:
		if (!data->uvd_power_gated) {
			if (uvd_index >= SMU8_MAX_HARDWARE_POWERLEVELS) {
				return -EINVAL;
			} else {
				vclk = uvd_table->entries[uvd_index].vclk;
				*((uint32_t *)value) = vclk;
				return 0;
			}
		}
		*((uint32_t *)value) = 0;
		return 0;
	case AMDGPU_PP_SENSOR_UVD_DCLK:
		if (!data->uvd_power_gated) {
			if (uvd_index >= SMU8_MAX_HARDWARE_POWERLEVELS) {
				return -EINVAL;
			} else {
				dclk = uvd_table->entries[uvd_index].dclk;
				*((uint32_t *)value) = dclk;
				return 0;
			}
		}
		*((uint32_t *)value) = 0;
		return 0;
	case AMDGPU_PP_SENSOR_VCE_ECCLK:
		if (!data->vce_power_gated) {
			if (vce_index >= SMU8_MAX_HARDWARE_POWERLEVELS) {
				return -EINVAL;
			} else {
				ecclk = vce_table->entries[vce_index].ecclk;
				*((uint32_t *)value) = ecclk;
				return 0;
			}
		}
		*((uint32_t *)value) = 0;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_LOAD:
		result = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetAverageGraphicsActivity);
		if (0 == result) {
			activity_percent = cgs_read_register(hwmgr->device, mmSMU_MP1_SRBM2P_ARG_0);
			activity_percent = activity_percent > 100 ? 100 : activity_percent;
		} else {
			activity_percent = 50;
		}
		*((uint32_t *)value) = activity_percent;
		return 0;
	case AMDGPU_PP_SENSOR_UVD_POWER:
		*((uint32_t *)value) = data->uvd_power_gated ? 0 : 1;
		return 0;
	case AMDGPU_PP_SENSOR_VCE_POWER:
		*((uint32_t *)value) = data->vce_power_gated ? 0 : 1;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uint32_t *)value) = smu8_thermal_get_temperature(hwmgr);
		return 0;
	default:
		return -EINVAL;
	}
}