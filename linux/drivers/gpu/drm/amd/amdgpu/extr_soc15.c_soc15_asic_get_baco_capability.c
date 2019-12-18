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
struct TYPE_2__ {struct amd_pm_funcs* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;
struct amd_pm_funcs {int (* get_asic_baco_capability ) (void*,int*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int stub1 (void*,int*) ; 

__attribute__((used)) static int soc15_asic_get_baco_capability(struct amdgpu_device *adev, bool *cap)
{
	void *pp_handle = adev->powerplay.pp_handle;
	const struct amd_pm_funcs *pp_funcs = adev->powerplay.pp_funcs;

	if (!pp_funcs || !pp_funcs->get_asic_baco_capability) {
		*cap = false;
		return -ENOENT;
	}

	return pp_funcs->get_asic_baco_capability(pp_handle, cap);
}