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
struct dma_fence {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_VM_CONTEXT_COMPUTE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_vm_fini (struct amdgpu_device*,struct amdgpu_vm*) ; 
 int amdgpu_vm_init (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ ,unsigned int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int init_kfd_vm (struct amdgpu_vm*,void**,struct dma_fence**) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_vm*) ; 
 struct amdgpu_vm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int amdgpu_amdkfd_gpuvm_create_process_vm(struct kgd_dev *kgd, unsigned int pasid,
					  void **vm, void **process_info,
					  struct dma_fence **ef)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	struct amdgpu_vm *new_vm;
	int ret;

	new_vm = kzalloc(sizeof(*new_vm), GFP_KERNEL);
	if (!new_vm)
		return -ENOMEM;

	/* Initialize AMDGPU part of the VM */
	ret = amdgpu_vm_init(adev, new_vm, AMDGPU_VM_CONTEXT_COMPUTE, pasid);
	if (ret) {
		pr_err("Failed init vm ret %d\n", ret);
		goto amdgpu_vm_init_fail;
	}

	/* Initialize KFD part of the VM and process info */
	ret = init_kfd_vm(new_vm, process_info, ef);
	if (ret)
		goto init_kfd_vm_fail;

	*vm = (void *) new_vm;

	return 0;

init_kfd_vm_fail:
	amdgpu_vm_fini(adev, new_vm);
amdgpu_vm_init_fail:
	kfree(new_vm);
	return ret;
}