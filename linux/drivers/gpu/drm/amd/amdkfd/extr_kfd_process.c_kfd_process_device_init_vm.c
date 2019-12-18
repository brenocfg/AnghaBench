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
struct kfd_process_device {int /*<<< orphan*/ * vm; struct file* drm_file; struct kfd_dev* dev; struct kfd_process* process; } ;
struct kfd_process {int /*<<< orphan*/  ef; int /*<<< orphan*/  kgd_process_info; int /*<<< orphan*/  pasid; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int amdgpu_amdkfd_gpuvm_acquire_process_vm (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_amdkfd_gpuvm_create_process_vm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_gpuvm_destroy_process_vm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_vm_set_task_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfd_process_device_free_bos (struct kfd_process_device*) ; 
 int kfd_process_device_init_cwsr_dgpu (struct kfd_process_device*) ; 
 int kfd_process_device_reserve_ib_mem (struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int kfd_process_device_init_vm(struct kfd_process_device *pdd,
			       struct file *drm_file)
{
	struct kfd_process *p;
	struct kfd_dev *dev;
	int ret;

	if (pdd->vm)
		return drm_file ? -EBUSY : 0;

	p = pdd->process;
	dev = pdd->dev;

	if (drm_file)
		ret = amdgpu_amdkfd_gpuvm_acquire_process_vm(
			dev->kgd, drm_file, p->pasid,
			&pdd->vm, &p->kgd_process_info, &p->ef);
	else
		ret = amdgpu_amdkfd_gpuvm_create_process_vm(dev->kgd, p->pasid,
			&pdd->vm, &p->kgd_process_info, &p->ef);
	if (ret) {
		pr_err("Failed to create process VM object\n");
		return ret;
	}

	amdgpu_vm_set_task_info(pdd->vm);

	ret = kfd_process_device_reserve_ib_mem(pdd);
	if (ret)
		goto err_reserve_ib_mem;
	ret = kfd_process_device_init_cwsr_dgpu(pdd);
	if (ret)
		goto err_init_cwsr;

	pdd->drm_file = drm_file;

	return 0;

err_init_cwsr:
err_reserve_ib_mem:
	kfd_process_device_free_bos(pdd);
	if (!drm_file)
		amdgpu_amdkfd_gpuvm_destroy_process_vm(dev->kgd, pdd->vm);
	pdd->vm = NULL;

	return ret;
}