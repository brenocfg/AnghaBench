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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct kgd_mem {int dummy; } ;
struct kfd_process_device {int /*<<< orphan*/  vm; } ;
struct kfd_process {int /*<<< orphan*/  mutex; } ;
struct kfd_ioctl_alloc_memory_of_gpu_args {int flags; scalar_t__ size; int /*<<< orphan*/  mmap_offset; int /*<<< orphan*/  gpu_id; int /*<<< orphan*/  handle; int /*<<< orphan*/  va_addr; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct file {int dummy; } ;
struct TYPE_2__ {long (* alloc_memory_of_gpu ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct kgd_mem**,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* free_memory_of_gpu ) (int /*<<< orphan*/ ,struct kgd_mem*) ;} ;

/* Variables and functions */
 long EFAULT ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct kfd_process_device*) ; 
 int KFD_IOC_ALLOC_MEM_FLAGS_PUBLIC ; 
 int KFD_IOC_ALLOC_MEM_FLAGS_VRAM ; 
 int /*<<< orphan*/  MAKE_HANDLE (int /*<<< orphan*/ ,int) ; 
 long PTR_ERR (struct kfd_process_device*) ; 
 struct kfd_process_device* kfd_bind_process_to_device (struct kfd_dev*,struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_dev_is_large_bar (struct kfd_dev*) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 int kfd_process_device_create_obj_handle (struct kfd_process_device*,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 long stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct kgd_mem**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct kgd_mem*) ; 

__attribute__((used)) static int kfd_ioctl_alloc_memory_of_gpu(struct file *filep,
					struct kfd_process *p, void *data)
{
	struct kfd_ioctl_alloc_memory_of_gpu_args *args = data;
	struct kfd_process_device *pdd;
	void *mem;
	struct kfd_dev *dev;
	int idr_handle;
	long err;
	uint64_t offset = args->mmap_offset;
	uint32_t flags = args->flags;

	if (args->size == 0)
		return -EINVAL;

	dev = kfd_device_by_id(args->gpu_id);
	if (!dev)
		return -EINVAL;

	if ((flags & KFD_IOC_ALLOC_MEM_FLAGS_PUBLIC) &&
		(flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM) &&
		!kfd_dev_is_large_bar(dev)) {
		pr_err("Alloc host visible vram on small bar is not allowed\n");
		return -EINVAL;
	}

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	if (IS_ERR(pdd)) {
		err = PTR_ERR(pdd);
		goto err_unlock;
	}

	err = dev->kfd2kgd->alloc_memory_of_gpu(
		dev->kgd, args->va_addr, args->size,
		pdd->vm, (struct kgd_mem **) &mem, &offset,
		flags);

	if (err)
		goto err_unlock;

	idr_handle = kfd_process_device_create_obj_handle(pdd, mem);
	if (idr_handle < 0) {
		err = -EFAULT;
		goto err_free;
	}

	mutex_unlock(&p->mutex);

	args->handle = MAKE_HANDLE(args->gpu_id, idr_handle);
	args->mmap_offset = offset;

	return 0;

err_free:
	dev->kfd2kgd->free_memory_of_gpu(dev->kgd, (struct kgd_mem *)mem);
err_unlock:
	mutex_unlock(&p->mutex);
	return err;
}