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
struct smu_context {TYPE_1__* ppt_funcs; } ;
struct pp_smu {struct dc_context* dm; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct amdgpu_device {struct smu_context smu; } ;
typedef  enum pp_smu_status { ____Placeholder_pp_smu_status } pp_smu_status ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_uclk_dpm_states ) (struct smu_context*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 int PP_SMU_RESULT_FAIL ; 
 int PP_SMU_RESULT_OK ; 
 int PP_SMU_RESULT_UNSUPPORTED ; 
 int /*<<< orphan*/  stub1 (struct smu_context*,unsigned int*,unsigned int*) ; 

enum pp_smu_status pp_nv_get_uclk_dpm_states(struct pp_smu *pp,
		unsigned int *clock_values_in_khz, unsigned int *num_states)
{
	const struct dc_context *ctx = pp->dm;
	struct amdgpu_device *adev = ctx->driver_context;
	struct smu_context *smu = &adev->smu;

	if (!smu->ppt_funcs)
		return PP_SMU_RESULT_UNSUPPORTED;

	if (!smu->ppt_funcs->get_uclk_dpm_states)
		return PP_SMU_RESULT_UNSUPPORTED;

	if (!smu->ppt_funcs->get_uclk_dpm_states(smu,
			clock_values_in_khz, num_states))
		return PP_SMU_RESULT_OK;

	return PP_SMU_RESULT_FAIL;
}