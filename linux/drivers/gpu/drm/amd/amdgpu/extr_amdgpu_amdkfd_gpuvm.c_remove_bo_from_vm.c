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
struct kfd_bo_va_list {int /*<<< orphan*/  bo_list; int /*<<< orphan*/  bo_va; scalar_t__ va; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_vm_bo_rmv (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kfd_bo_va_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,struct kfd_bo_va_list*) ; 

__attribute__((used)) static void remove_bo_from_vm(struct amdgpu_device *adev,
		struct kfd_bo_va_list *entry, unsigned long size)
{
	pr_debug("\t remove VA 0x%llx - 0x%llx in entry %p\n",
			entry->va,
			entry->va + size, entry);
	amdgpu_vm_bo_rmv(adev, entry->bo_va);
	list_del(&entry->bo_list);
	kfree(entry);
}