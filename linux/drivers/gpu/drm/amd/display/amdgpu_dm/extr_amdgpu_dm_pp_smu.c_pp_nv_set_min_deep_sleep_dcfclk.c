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
struct smu_context {int /*<<< orphan*/  funcs; } ;
struct pp_smu {struct dc_context* dm; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct amdgpu_device {struct smu_context smu; } ;
typedef  enum pp_smu_status { ____Placeholder_pp_smu_status } pp_smu_status ;

/* Variables and functions */
 int PP_SMU_RESULT_FAIL ; 
 int PP_SMU_RESULT_OK ; 
 int PP_SMU_RESULT_UNSUPPORTED ; 
 scalar_t__ smu_set_deep_sleep_dcefclk (struct smu_context*,int) ; 

enum pp_smu_status pp_nv_set_min_deep_sleep_dcfclk(struct pp_smu *pp, int mhz)
{
	const struct dc_context *ctx = pp->dm;
	struct amdgpu_device *adev = ctx->driver_context;
	struct smu_context *smu = &adev->smu;

	if (!smu->funcs)
		return PP_SMU_RESULT_UNSUPPORTED;

	/* 0: successful or smu.funcs->set_deep_sleep_dcefclk = NULL;1: fail */
	if (smu_set_deep_sleep_dcefclk(smu, mhz))
		return PP_SMU_RESULT_FAIL;

	return PP_SMU_RESULT_OK;
}