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
struct smu10_hwmgr {int /*<<< orphan*/  vcn_power_gated; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_GFX_MCLK 131 
#define  AMDGPU_PP_SENSOR_GFX_SCLK 130 
#define  AMDGPU_PP_SENSOR_GPU_TEMP 129 
#define  AMDGPU_PP_SENSOR_VCN_POWER_STATE 128 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_GetFclkFrequency ; 
 int /*<<< orphan*/  PPSMC_MSG_GetGfxclkFrequency ; 
 int smu10_thermal_get_temperature (struct pp_hwmgr*) ; 
 int smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu10_read_sensor(struct pp_hwmgr *hwmgr, int idx,
			  void *value, int *size)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);
	uint32_t sclk, mclk;
	int ret = 0;

	switch (idx) {
	case AMDGPU_PP_SENSOR_GFX_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetGfxclkFrequency);
		sclk = smum_get_argument(hwmgr);
			/* in units of 10KHZ */
		*((uint32_t *)value) = sclk * 100;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GFX_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetFclkFrequency);
		mclk = smum_get_argument(hwmgr);
			/* in units of 10KHZ */
		*((uint32_t *)value) = mclk * 100;
		*size = 4;
		break;
	case AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uint32_t *)value) = smu10_thermal_get_temperature(hwmgr);
		break;
	case AMDGPU_PP_SENSOR_VCN_POWER_STATE:
		*(uint32_t *)value =  smu10_data->vcn_power_gated ? 0 : 1;
		*size = 4;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}