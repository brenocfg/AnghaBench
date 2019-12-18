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
struct smu7_hwmgr {int soft_regs_start; int vr_config; int /*<<< orphan*/  vce_power_gated; int /*<<< orphan*/  uvd_power_gated; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ backend; } ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GFX_MCLK 136 
#define  AMDGPU_PP_SENSOR_GFX_SCLK 135 
#define  AMDGPU_PP_SENSOR_GPU_LOAD 134 
#define  AMDGPU_PP_SENSOR_GPU_POWER 133 
#define  AMDGPU_PP_SENSOR_GPU_TEMP 132 
#define  AMDGPU_PP_SENSOR_MEM_LOAD 131 
#define  AMDGPU_PP_SENSOR_UVD_POWER 130 
#define  AMDGPU_PP_SENSOR_VCE_POWER 129 
#define  AMDGPU_PP_SENSOR_VDDGFX 128 
 int /*<<< orphan*/  AverageGraphicsActivity ; 
 int /*<<< orphan*/  AverageMemoryActivity ; 
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int EINVAL ; 
 int PHM_READ_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE1_VID ; 
 int /*<<< orphan*/  PLANE2_VID ; 
 int /*<<< orphan*/  PPSMC_MSG_API_GetMclkFrequency ; 
 int /*<<< orphan*/  PPSMC_MSG_API_GetSclkFrequency ; 
 int /*<<< orphan*/  PWR_SVI2_STATUS ; 
 int /*<<< orphan*/  SMU_SoftRegisters ; 
 int cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_vddc (int) ; 
 int /*<<< orphan*/  mmSMC_MSG_ARG_0 ; 
 int smu7_get_gpu_power (struct pp_hwmgr*,int*) ; 
 int smu7_thermal_get_temperature (struct pp_hwmgr*) ; 
 int smum_get_offsetof (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_read_sensor(struct pp_hwmgr *hwmgr, int idx,
			    void *value, int *size)
{
	uint32_t sclk, mclk, activity_percent;
	uint32_t offset, val_vid;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	/* size must be at least 4 bytes for all sensors */
	if (*size < 4)
		return -EINVAL;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GFX_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetSclkFrequency);
		sclk = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);
		*((uint32_t *)value) = sclk;
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GFX_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetMclkFrequency);
		mclk = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);
		*((uint32_t *)value) = mclk;
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_LOAD:
	case AMDGPU_PP_SENSOR_MEM_LOAD:
		offset = data->soft_regs_start + smum_get_offsetof(hwmgr,
								SMU_SoftRegisters,
								(idx == AMDGPU_PP_SENSOR_GPU_LOAD) ?
								AverageGraphicsActivity:
								AverageMemoryActivity);

		activity_percent = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, offset);
		activity_percent += 0x80;
		activity_percent >>= 8;
		*((uint32_t *)value) = activity_percent > 100 ? 100 : activity_percent;
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uint32_t *)value) = smu7_thermal_get_temperature(hwmgr);
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_UVD_POWER:
		*((uint32_t *)value) = data->uvd_power_gated ? 0 : 1;
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_VCE_POWER:
		*((uint32_t *)value) = data->vce_power_gated ? 0 : 1;
		*size = 4;
		return 0;
	case AMDGPU_PP_SENSOR_GPU_POWER:
		return smu7_get_gpu_power(hwmgr, (uint32_t *)value);
	case AMDGPU_PP_SENSOR_VDDGFX:
		if ((data->vr_config & 0xff) == 0x2)
			val_vid = PHM_READ_INDIRECT_FIELD(hwmgr->device,
					CGS_IND_REG__SMC, PWR_SVI2_STATUS, PLANE2_VID);
		else
			val_vid = PHM_READ_INDIRECT_FIELD(hwmgr->device,
					CGS_IND_REG__SMC, PWR_SVI2_STATUS, PLANE1_VID);

		*((uint32_t *)value) = (uint32_t)convert_to_vddc(val_vid);
		return 0;
	default:
		return -EINVAL;
	}
}