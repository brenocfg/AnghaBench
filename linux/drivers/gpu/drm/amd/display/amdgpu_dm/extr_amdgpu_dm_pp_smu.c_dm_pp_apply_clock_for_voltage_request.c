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
struct pp_display_clock_request {int /*<<< orphan*/  clock_type; int /*<<< orphan*/  clock_freq_in_khz; int /*<<< orphan*/  member_0; } ;
struct dm_pp_clock_for_voltage_req {int /*<<< orphan*/  clocks_in_khz; int /*<<< orphan*/  clk_type; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct TYPE_8__ {TYPE_3__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_4__ smu; TYPE_2__ powerplay; } ;
struct TYPE_7__ {scalar_t__ display_clock_voltage_request; } ;
struct TYPE_5__ {int (* display_clock_voltage_request ) (int /*<<< orphan*/ ,struct pp_display_clock_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dc_to_pp_clock_type (int /*<<< orphan*/ ) ; 
 int smu_display_clock_voltage_request (TYPE_4__*,struct pp_display_clock_request*) ; 
 int stub1 (int /*<<< orphan*/ ,struct pp_display_clock_request*) ; 

bool dm_pp_apply_clock_for_voltage_request(
	const struct dc_context *ctx,
	struct dm_pp_clock_for_voltage_req *clock_for_voltage_req)
{
	struct amdgpu_device *adev = ctx->driver_context;
	struct pp_display_clock_request pp_clock_request = {0};
	int ret = 0;

	pp_clock_request.clock_type = dc_to_pp_clock_type(clock_for_voltage_req->clk_type);
	pp_clock_request.clock_freq_in_khz = clock_for_voltage_req->clocks_in_khz;

	if (!pp_clock_request.clock_type)
		return false;

	if (adev->powerplay.pp_funcs && adev->powerplay.pp_funcs->display_clock_voltage_request)
		ret = adev->powerplay.pp_funcs->display_clock_voltage_request(
			adev->powerplay.pp_handle,
			&pp_clock_request);
	else if (adev->smu.funcs &&
		 adev->smu.funcs->display_clock_voltage_request)
		ret = smu_display_clock_voltage_request(&adev->smu,
							&pp_clock_request);
	if (ret)
		return false;
	return true;
}