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
struct kgd_dev {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_vm_fini (struct amdgpu_device*,struct amdgpu_vm*) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*) ; 

void amdgpu_amdkfd_gpuvm_destroy_process_vm(struct kgd_dev *kgd, void *vm)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	struct amdgpu_vm *avm = (struct amdgpu_vm *)vm;

	if (WARN_ON(!kgd || !vm))
		return;

	pr_debug("Destroying process vm %p\n", vm);

	/* Release the VM context */
	amdgpu_vm_fini(adev, avm);
	kfree(vm);
}