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
struct si_ps {int dummy; } ;
struct ni_power_info {struct si_ps current_ps; } ;
struct amdgpu_ps {struct si_ps* ps_priv; } ;
struct evergreen_power_info {struct amdgpu_ps current_rps; } ;
struct TYPE_3__ {struct amdgpu_ps* current_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 struct ni_power_info* ni_get_pi (struct amdgpu_device*) ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static void ni_update_current_ps(struct amdgpu_device *adev,
			  struct amdgpu_ps *rps)
{
	struct si_ps *new_ps = si_get_ps(rps);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct ni_power_info *ni_pi = ni_get_pi(adev);

	eg_pi->current_rps = *rps;
	ni_pi->current_ps = *new_ps;
	eg_pi->current_rps.ps_priv = &ni_pi->current_ps;
	adev->pm.dpm.current_ps = &eg_pi->current_rps;
}