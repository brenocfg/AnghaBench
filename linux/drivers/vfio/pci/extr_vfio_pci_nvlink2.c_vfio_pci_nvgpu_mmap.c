#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_flags; struct vfio_pci_region* vm_private_data; } ;
struct vfio_pci_region {struct vfio_pci_nvgpu_data* data; } ;
struct vfio_pci_nvgpu_data {scalar_t__ useraddr; scalar_t__ size; int /*<<< orphan*/  gpu_hpa; int /*<<< orphan*/  mem; TYPE_1__* mm; } ;
struct vfio_pci_device {int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  VM_PFNMAP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 scalar_t__ mm_iommu_newdev (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_vfio_pci_nvgpu_mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  vfio_pci_nvgpu_mmap_vmops ; 
 int /*<<< orphan*/  vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int vfio_pci_nvgpu_mmap(struct vfio_pci_device *vdev,
		struct vfio_pci_region *region, struct vm_area_struct *vma)
{
	int ret;
	struct vfio_pci_nvgpu_data *data = region->data;

	if (data->useraddr)
		return -EPERM;

	if (vma->vm_end - vma->vm_start > data->size)
		return -EINVAL;

	vma->vm_private_data = region;
	vma->vm_flags |= VM_PFNMAP;
	vma->vm_ops = &vfio_pci_nvgpu_mmap_vmops;

	/*
	 * Calling mm_iommu_newdev() here once as the region is not
	 * registered yet and therefore right initialization will happen now.
	 * Other places will use mm_iommu_find() which returns
	 * registered @mem and does not go gup().
	 */
	data->useraddr = vma->vm_start;
	data->mm = current->mm;

	atomic_inc(&data->mm->mm_count);
	ret = (int) mm_iommu_newdev(data->mm, data->useraddr,
			vma_pages(vma), data->gpu_hpa, &data->mem);

	trace_vfio_pci_nvgpu_mmap(vdev->pdev, data->gpu_hpa, data->useraddr,
			vma->vm_end - vma->vm_start, ret);

	return ret;
}