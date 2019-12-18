#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_va {int dummy; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VA_OP_MAP ; 
 scalar_t__ AMDGPU_VA_OP_REPLACE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ERESTARTSYS ; 
 int amdgpu_vm_bo_update (struct amdgpu_device*,struct amdgpu_bo_va*,int) ; 
 int amdgpu_vm_clear_freed (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_vm_ready (struct amdgpu_vm*) ; 
 int amdgpu_vm_update_directories (struct amdgpu_device*,struct amdgpu_vm*) ; 

__attribute__((used)) static void amdgpu_gem_va_update_vm(struct amdgpu_device *adev,
				    struct amdgpu_vm *vm,
				    struct amdgpu_bo_va *bo_va,
				    uint32_t operation)
{
	int r;

	if (!amdgpu_vm_ready(vm))
		return;

	r = amdgpu_vm_clear_freed(adev, vm, NULL);
	if (r)
		goto error;

	if (operation == AMDGPU_VA_OP_MAP ||
	    operation == AMDGPU_VA_OP_REPLACE) {
		r = amdgpu_vm_bo_update(adev, bo_va, false);
		if (r)
			goto error;
	}

	r = amdgpu_vm_update_directories(adev, vm);

error:
	if (r && r != -ERESTARTSYS)
		DRM_ERROR("Couldn't update BO_VA (%d)\n", r);
}