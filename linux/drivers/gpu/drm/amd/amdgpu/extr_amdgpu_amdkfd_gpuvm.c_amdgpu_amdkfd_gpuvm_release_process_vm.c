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
 int /*<<< orphan*/  amdgpu_vm_release_compute (struct amdgpu_device*,struct amdgpu_vm*) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*) ; 

void amdgpu_amdkfd_gpuvm_release_process_vm(struct kgd_dev *kgd, void *vm)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
        struct amdgpu_vm *avm = (struct amdgpu_vm *)vm;

	if (WARN_ON(!kgd || !vm))
                return;

        pr_debug("Releasing process vm %p\n", vm);

        /* The original pasid of amdgpu vm has already been
         * released during making a amdgpu vm to a compute vm
         * The current pasid is managed by kfd and will be
         * released on kfd process destroy. Set amdgpu pasid
         * to 0 to avoid duplicate release.
         */
	amdgpu_vm_release_compute(adev, avm);
}