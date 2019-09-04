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
struct TYPE_2__ {int /*<<< orphan*/  num_prt_users; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_vm_update_prt_state (struct amdgpu_device*) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vm_prt_put(struct amdgpu_device *adev)
{
	if (atomic_dec_return(&adev->vm_manager.num_prt_users) == 0)
		amdgpu_vm_update_prt_state(adev);
}