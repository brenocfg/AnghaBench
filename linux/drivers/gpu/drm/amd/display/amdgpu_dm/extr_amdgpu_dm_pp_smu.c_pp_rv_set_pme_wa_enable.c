#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pp_smu {struct dc_context* dm; } ;
struct dc_context {struct amdgpu_device* driver_context; } ;
struct TYPE_4__ {scalar_t__ funcs; } ;
struct TYPE_3__ {struct amd_pm_funcs* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {TYPE_2__ smu; TYPE_1__ powerplay; } ;
struct amd_pm_funcs {int /*<<< orphan*/  (* notify_smu_enable_pwe ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  smu_notify_smu_enable_pwe (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void pp_rv_set_pme_wa_enable(struct pp_smu *pp)
{
	const struct dc_context *ctx = pp->dm;
	struct amdgpu_device *adev = ctx->driver_context;
	void *pp_handle = adev->powerplay.pp_handle;
	const struct amd_pm_funcs *pp_funcs = adev->powerplay.pp_funcs;

	if (pp_funcs && pp_funcs->notify_smu_enable_pwe)
		pp_funcs->notify_smu_enable_pwe(pp_handle);
	else if (adev->smu.funcs)
		smu_notify_smu_enable_pwe(&adev->smu);
}