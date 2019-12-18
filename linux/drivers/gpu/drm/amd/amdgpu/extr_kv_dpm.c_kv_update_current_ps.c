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
struct kv_ps {int dummy; } ;
struct amdgpu_ps {struct kv_ps* ps_priv; } ;
struct kv_power_info {struct amdgpu_ps current_rps; struct kv_ps current_ps; } ;
struct TYPE_4__ {struct amdgpu_ps* current_ps; } ;
struct TYPE_3__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 struct kv_ps* kv_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static void kv_update_current_ps(struct amdgpu_device *adev,
				 struct amdgpu_ps *rps)
{
	struct kv_ps *new_ps = kv_get_ps(rps);
	struct kv_power_info *pi = kv_get_pi(adev);

	pi->current_rps = *rps;
	pi->current_ps = *new_ps;
	pi->current_rps.ps_priv = &pi->current_ps;
	adev->pm.dpm.current_ps = &pi->current_rps;
}