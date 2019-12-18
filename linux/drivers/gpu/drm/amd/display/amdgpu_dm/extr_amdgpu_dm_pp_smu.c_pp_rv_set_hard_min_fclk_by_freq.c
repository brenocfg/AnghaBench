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
struct pp_smu {struct dc_context* dm; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct TYPE_2__ {struct amd_pm_funcs* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;
struct amd_pm_funcs {int /*<<< orphan*/  (* set_hard_min_fclk_by_freq ) (void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,int) ; 

void pp_rv_set_hard_min_fclk_by_freq(struct pp_smu *pp, int mhz)
{
	const struct dc_context *ctx = pp->dm;
	struct amdgpu_device *adev = ctx->driver_context;
	void *pp_handle = adev->powerplay.pp_handle;
	const struct amd_pm_funcs *pp_funcs = adev->powerplay.pp_funcs;

	if (!pp_funcs || !pp_funcs->set_hard_min_fclk_by_freq)
		return;

	pp_funcs->set_hard_min_fclk_by_freq(pp_handle, mhz);
}