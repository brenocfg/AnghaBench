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
struct kgd_mem {int dummy; } ;
struct kfd_process_device {int dummy; } ;
struct kfd_process {int /*<<< orphan*/  mutex; } ;
struct kfd_ioctl_free_memory_of_gpu_args {int /*<<< orphan*/  handle; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GET_GPU_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_IDR_HANDLE (int /*<<< orphan*/ ) ; 
 int amdgpu_amdkfd_gpuvm_free_memory_of_gpu (int /*<<< orphan*/ ,struct kgd_mem*) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 struct kfd_process_device* kfd_get_process_device_data (struct kfd_dev*,struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_process_device_remove_obj_handle (struct kfd_process_device*,int /*<<< orphan*/ ) ; 
 void* kfd_process_device_translate_handle (struct kfd_process_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int kfd_ioctl_free_memory_of_gpu(struct file *filep,
					struct kfd_process *p, void *data)
{
	struct kfd_ioctl_free_memory_of_gpu_args *args = data;
	struct kfd_process_device *pdd;
	void *mem;
	struct kfd_dev *dev;
	int ret;

	dev = kfd_device_by_id(GET_GPU_ID(args->handle));
	if (!dev)
		return -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_get_process_device_data(dev, p);
	if (!pdd) {
		pr_err("Process device data doesn't exist\n");
		ret = -EINVAL;
		goto err_unlock;
	}

	mem = kfd_process_device_translate_handle(
		pdd, GET_IDR_HANDLE(args->handle));
	if (!mem) {
		ret = -EINVAL;
		goto err_unlock;
	}

	ret = amdgpu_amdkfd_gpuvm_free_memory_of_gpu(dev->kgd,
						(struct kgd_mem *)mem);

	/* If freeing the buffer failed, leave the handle in place for
	 * clean-up during process tear-down.
	 */
	if (!ret)
		kfd_process_device_remove_obj_handle(
			pdd, GET_IDR_HANDLE(args->handle));

err_unlock:
	mutex_unlock(&p->mutex);
	return ret;
}