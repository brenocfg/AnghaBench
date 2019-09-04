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
struct pp_smu_display_requirement_rv {int /*<<< orphan*/  hard_min_fclk_khz; int /*<<< orphan*/  hard_min_dcefclk_khz; } ;
struct pp_smu {struct dc_context* ctx; } ;
struct pp_display_clock_request {int /*<<< orphan*/  clock_freq_in_khz; int /*<<< orphan*/  clock_type; int /*<<< orphan*/  member_0; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct TYPE_2__ {struct amd_pm_funcs* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;
struct amd_pm_funcs {int /*<<< orphan*/  (* display_clock_voltage_request ) (void*,struct pp_display_clock_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  amd_pp_dcf_clock ; 
 int /*<<< orphan*/  amd_pp_f_clock ; 
 int /*<<< orphan*/  stub1 (void*,struct pp_display_clock_request*) ; 
 int /*<<< orphan*/  stub2 (void*,struct pp_display_clock_request*) ; 

void pp_rv_set_display_requirement(struct pp_smu *pp,
		struct pp_smu_display_requirement_rv *req)
{
	struct dc_context *ctx = pp->ctx;
	struct amdgpu_device *adev = ctx->driver_context;
	void *pp_handle = adev->powerplay.pp_handle;
	const struct amd_pm_funcs *pp_funcs = adev->powerplay.pp_funcs;
	struct pp_display_clock_request clock = {0};

	if (!pp_funcs || !pp_funcs->display_clock_voltage_request)
		return;

	clock.clock_type = amd_pp_dcf_clock;
	clock.clock_freq_in_khz = req->hard_min_dcefclk_khz;
	pp_funcs->display_clock_voltage_request(pp_handle, &clock);

	clock.clock_type = amd_pp_f_clock;
	clock.clock_freq_in_khz = req->hard_min_fclk_khz;
	pp_funcs->display_clock_voltage_request(pp_handle, &clock);
}