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
struct TYPE_2__ {int /*<<< orphan*/  pasid_idr; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_vmid_mgr_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_is_empty (int /*<<< orphan*/ *) ; 

void amdgpu_vm_manager_fini(struct amdgpu_device *adev)
{
	WARN_ON(!idr_is_empty(&adev->vm_manager.pasid_idr));
	idr_destroy(&adev->vm_manager.pasid_idr);

	amdgpu_vmid_mgr_fini(adev);
}