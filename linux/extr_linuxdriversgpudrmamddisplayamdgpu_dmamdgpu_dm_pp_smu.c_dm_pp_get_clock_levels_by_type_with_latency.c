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
struct pp_clock_levels_with_latency {int /*<<< orphan*/  member_0; } ;
struct dm_pp_clock_levels_with_latency {int dummy; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct TYPE_2__ {struct amd_pm_funcs* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;
struct amd_pm_funcs {scalar_t__ (* get_clock_by_type_with_latency ) (void*,int /*<<< orphan*/ ,struct pp_clock_levels_with_latency*) ;} ;
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  dc_to_pp_clock_type (int) ; 
 int /*<<< orphan*/  pp_to_dc_clock_levels_with_latency (struct pp_clock_levels_with_latency*,struct dm_pp_clock_levels_with_latency*,int) ; 
 scalar_t__ stub1 (void*,int /*<<< orphan*/ ,struct pp_clock_levels_with_latency*) ; 

bool dm_pp_get_clock_levels_by_type_with_latency(
	const struct dc_context *ctx,
	enum dm_pp_clock_type clk_type,
	struct dm_pp_clock_levels_with_latency *clk_level_info)
{
	struct amdgpu_device *adev = ctx->driver_context;
	void *pp_handle = adev->powerplay.pp_handle;
	struct pp_clock_levels_with_latency pp_clks = { 0 };
	const struct amd_pm_funcs *pp_funcs = adev->powerplay.pp_funcs;

	if (!pp_funcs || !pp_funcs->get_clock_by_type_with_latency)
		return false;

	if (pp_funcs->get_clock_by_type_with_latency(pp_handle,
						     dc_to_pp_clock_type(clk_type),
						     &pp_clks))
		return false;

	pp_to_dc_clock_levels_with_latency(&pp_clks, clk_level_info, clk_type);

	return true;
}