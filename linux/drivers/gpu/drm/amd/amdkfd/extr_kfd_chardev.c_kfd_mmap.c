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
struct vm_area_struct {unsigned long vm_pgoff; } ;
struct kfd_process {int dummy; } ;
struct kfd_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct kfd_process*) ; 
 unsigned int KFD_MMAP_GPU_ID_GET (unsigned long) ; 
 unsigned long KFD_MMAP_OFFSET_VALUE_GET (unsigned long) ; 
#define  KFD_MMAP_TYPE_DOORBELL 131 
#define  KFD_MMAP_TYPE_EVENTS 130 
 unsigned long KFD_MMAP_TYPE_MASK ; 
#define  KFD_MMAP_TYPE_MMIO 129 
#define  KFD_MMAP_TYPE_RESERVED_MEM 128 
 int PTR_ERR (struct kfd_process*) ; 
 int /*<<< orphan*/  current ; 
 struct kfd_dev* kfd_device_by_id (unsigned int) ; 
 int kfd_doorbell_mmap (struct kfd_dev*,struct kfd_process*,struct vm_area_struct*) ; 
 int kfd_event_mmap (struct kfd_process*,struct vm_area_struct*) ; 
 struct kfd_process* kfd_get_process (int /*<<< orphan*/ ) ; 
 int kfd_mmio_mmap (struct kfd_dev*,struct kfd_process*,struct vm_area_struct*) ; 
 int kfd_reserved_mem_mmap (struct kfd_dev*,struct kfd_process*,struct vm_area_struct*) ; 

__attribute__((used)) static int kfd_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct kfd_process *process;
	struct kfd_dev *dev = NULL;
	unsigned long vm_pgoff;
	unsigned int gpu_id;

	process = kfd_get_process(current);
	if (IS_ERR(process))
		return PTR_ERR(process);

	vm_pgoff = vma->vm_pgoff;
	vma->vm_pgoff = KFD_MMAP_OFFSET_VALUE_GET(vm_pgoff);
	gpu_id = KFD_MMAP_GPU_ID_GET(vm_pgoff);
	if (gpu_id)
		dev = kfd_device_by_id(gpu_id);

	switch (vm_pgoff & KFD_MMAP_TYPE_MASK) {
	case KFD_MMAP_TYPE_DOORBELL:
		if (!dev)
			return -ENODEV;
		return kfd_doorbell_mmap(dev, process, vma);

	case KFD_MMAP_TYPE_EVENTS:
		return kfd_event_mmap(process, vma);

	case KFD_MMAP_TYPE_RESERVED_MEM:
		if (!dev)
			return -ENODEV;
		return kfd_reserved_mem_mmap(dev, process, vma);
	case KFD_MMAP_TYPE_MMIO:
		if (!dev)
			return -ENODEV;
		return kfd_mmio_mmap(dev, process, vma);
	}

	return -EFAULT;
}