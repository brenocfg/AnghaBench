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
struct dma_fence {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_va_mapping {int flags; } ;

/* Variables and functions */
 int AMDGPU_PTE_PRT ; 
 int /*<<< orphan*/  amdgpu_vm_add_prt_cb (struct amdgpu_device*,struct dma_fence*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_bo_va_mapping*) ; 

__attribute__((used)) static void amdgpu_vm_free_mapping(struct amdgpu_device *adev,
				   struct amdgpu_vm *vm,
				   struct amdgpu_bo_va_mapping *mapping,
				   struct dma_fence *fence)
{
	if (mapping->flags & AMDGPU_PTE_PRT)
		amdgpu_vm_add_prt_cb(adev, fence);
	kfree(mapping);
}