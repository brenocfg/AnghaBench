#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  num_prt_users; } ;
struct TYPE_5__ {TYPE_1__* gmc_funcs; } ;
struct amdgpu_device {TYPE_3__ vm_manager; TYPE_2__ gmc; } ;
struct TYPE_4__ {int /*<<< orphan*/  set_prt; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_vm_update_prt_state (struct amdgpu_device*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vm_prt_get(struct amdgpu_device *adev)
{
	if (!adev->gmc.gmc_funcs->set_prt)
		return;

	if (atomic_inc_return(&adev->vm_manager.num_prt_users) == 1)
		amdgpu_vm_update_prt_state(adev);
}