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
struct file {struct drm_file* private_data; } ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_vm {scalar_t__ process_info; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int amdgpu_vm_make_compute (struct amdgpu_device*,struct amdgpu_vm*,unsigned int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int init_kfd_vm (struct amdgpu_vm*,void**,struct dma_fence**) ; 

int amdgpu_amdkfd_gpuvm_acquire_process_vm(struct kgd_dev *kgd,
					   struct file *filp, unsigned int pasid,
					   void **vm, void **process_info,
					   struct dma_fence **ef)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	struct drm_file *drm_priv = filp->private_data;
	struct amdgpu_fpriv *drv_priv = drm_priv->driver_priv;
	struct amdgpu_vm *avm = &drv_priv->vm;
	int ret;

	/* Already a compute VM? */
	if (avm->process_info)
		return -EINVAL;

	/* Convert VM into a compute VM */
	ret = amdgpu_vm_make_compute(adev, avm, pasid);
	if (ret)
		return ret;

	/* Initialize KFD part of the VM and process info */
	ret = init_kfd_vm(avm, process_info, ef);
	if (ret)
		return ret;

	*vm = (void *)avm;

	return 0;
}