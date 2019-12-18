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
struct vm_area_struct {unsigned int vm_pgoff; int vm_end; int vm_start; int vm_flags; struct vfio_platform_device* vm_private_data; } ;
struct vfio_platform_device {unsigned int num_regions; TYPE_1__* regions; } ;
struct TYPE_2__ {int flags; int type; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int VFIO_PLATFORM_OFFSET_SHIFT ; 
 int VFIO_PLATFORM_REGION_TYPE_MMIO ; 
 int VFIO_PLATFORM_REGION_TYPE_PIO ; 
 int VFIO_REGION_INFO_FLAG_MMAP ; 
 int VFIO_REGION_INFO_FLAG_READ ; 
 int VFIO_REGION_INFO_FLAG_WRITE ; 
 int VM_READ ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int vfio_platform_mmap_mmio (TYPE_1__,struct vm_area_struct*) ; 

__attribute__((used)) static int vfio_platform_mmap(void *device_data, struct vm_area_struct *vma)
{
	struct vfio_platform_device *vdev = device_data;
	unsigned int index;

	index = vma->vm_pgoff >> (VFIO_PLATFORM_OFFSET_SHIFT - PAGE_SHIFT);

	if (vma->vm_end < vma->vm_start)
		return -EINVAL;
	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;
	if (index >= vdev->num_regions)
		return -EINVAL;
	if (vma->vm_start & ~PAGE_MASK)
		return -EINVAL;
	if (vma->vm_end & ~PAGE_MASK)
		return -EINVAL;

	if (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_MMAP))
		return -EINVAL;

	if (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_READ)
			&& (vma->vm_flags & VM_READ))
		return -EINVAL;

	if (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_WRITE)
			&& (vma->vm_flags & VM_WRITE))
		return -EINVAL;

	vma->vm_private_data = vdev;

	if (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_MMIO)
		return vfio_platform_mmap_mmio(vdev->regions[index], vma);

	else if (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_PIO)
		return -EINVAL; /* not implemented */

	return -EINVAL;
}