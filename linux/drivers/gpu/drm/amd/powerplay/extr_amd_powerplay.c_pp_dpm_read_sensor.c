#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  ulMaxRPM; int /*<<< orphan*/  ulMinRPM; } ;
struct TYPE_5__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; TYPE_3__* hwmgr_func; TYPE_2__ thermal_controller; int /*<<< orphan*/  pstate_mclk; int /*<<< orphan*/  pstate_sclk; int /*<<< orphan*/  pm_en; } ;
struct TYPE_6__ {int (* read_sensor ) (struct pp_hwmgr*,int,void*,int*) ;} ;

/* Variables and functions */
#define  AMDGPU_PP_SENSOR_MAX_FAN_RPM 131 
#define  AMDGPU_PP_SENSOR_MIN_FAN_RPM 130 
#define  AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK 129 
#define  AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK 128 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct pp_hwmgr*,int,void*,int*) ; 

__attribute__((used)) static int pp_dpm_read_sensor(void *handle, int idx,
			      void *value, int *size)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en || !value)
		return -EINVAL;

	switch (idx) {
	case AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK:
		*((uint32_t *)value) = hwmgr->pstate_sclk;
		return 0;
	case AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK:
		*((uint32_t *)value) = hwmgr->pstate_mclk;
		return 0;
	case AMDGPU_PP_SENSOR_MIN_FAN_RPM:
		*((uint32_t *)value) = hwmgr->thermal_controller.fanInfo.ulMinRPM;
		return 0;
	case AMDGPU_PP_SENSOR_MAX_FAN_RPM:
		*((uint32_t *)value) = hwmgr->thermal_controller.fanInfo.ulMaxRPM;
		return 0;
	default:
		mutex_lock(&hwmgr->smu_lock);
		ret = hwmgr->hwmgr_func->read_sensor(hwmgr, idx, value, size);
		mutex_unlock(&hwmgr->smu_lock);
		return ret;
	}
}