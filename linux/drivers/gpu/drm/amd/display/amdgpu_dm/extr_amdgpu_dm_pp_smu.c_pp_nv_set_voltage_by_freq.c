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
struct pp_display_clock_request {int clock_freq_in_khz; int /*<<< orphan*/  clock_type; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct amdgpu_device {struct smu_context smu; } ;
typedef  enum pp_smu_status { ____Placeholder_pp_smu_status } pp_smu_status ;
typedef  enum pp_smu_nv_clock_id { ____Placeholder_pp_smu_nv_clock_id } pp_smu_nv_clock_id ;

/* Variables and functions */
#define  PP_SMU_NV_DISPCLK 130 
#define  PP_SMU_NV_PHYCLK 129 
#define  PP_SMU_NV_PIXELCLK 128 
 int PP_SMU_RESULT_FAIL ; 
 int PP_SMU_RESULT_OK ; 
 int PP_SMU_RESULT_UNSUPPORTED ; 
 int /*<<< orphan*/  amd_pp_disp_clock ; 
 int /*<<< orphan*/  amd_pp_phy_clock ; 
 int /*<<< orphan*/  amd_pp_pixel_clock ; 
 scalar_t__ smu_display_clock_voltage_request (struct smu_context*,struct pp_display_clock_request*) ; 

enum pp_smu_status pp_nv_set_voltage_by_freq(struct pp_smu *pp,
		enum pp_smu_nv_clock_id clock_id, int mhz)
{
	const struct dc_context *ctx = pp->dm;
	struct amdgpu_device *adev = ctx->driver_context;
	struct smu_context *smu = &adev->smu;
	struct pp_display_clock_request clock_req;

	if (!smu->funcs)
		return PP_SMU_RESULT_UNSUPPORTED;

	switch (clock_id) {
	case PP_SMU_NV_DISPCLK:
		clock_req.clock_type = amd_pp_disp_clock;
		break;
	case PP_SMU_NV_PHYCLK:
		clock_req.clock_type = amd_pp_phy_clock;
		break;
	case PP_SMU_NV_PIXELCLK:
		clock_req.clock_type = amd_pp_pixel_clock;
		break;
	default:
		break;
	}
	clock_req.clock_freq_in_khz = mhz * 1000;

	/* 0: successful or smu.funcs->display_clock_voltage_request = NULL
	 * 1: fail
	 */
	if (smu_display_clock_voltage_request(smu, &clock_req))
		return PP_SMU_RESULT_FAIL;

	return PP_SMU_RESULT_OK;
}