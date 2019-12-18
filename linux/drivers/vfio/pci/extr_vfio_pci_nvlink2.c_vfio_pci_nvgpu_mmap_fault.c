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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned int address; struct vm_area_struct* vma; } ;
struct vm_area_struct {unsigned int vm_start; unsigned int vm_pgoff; struct vfio_pci_region* vm_private_data; } ;
struct vfio_pci_region {struct vfio_pci_nvgpu_data* data; } ;
struct vfio_pci_nvgpu_data {unsigned int gpu_hpa; int /*<<< orphan*/  gpdev; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 unsigned int VFIO_PCI_OFFSET_SHIFT ; 
 int /*<<< orphan*/  trace_vfio_pci_nvgpu_mmap_fault (int /*<<< orphan*/ ,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_pfn (struct vm_area_struct*,unsigned int,unsigned long) ; 

__attribute__((used)) static vm_fault_t vfio_pci_nvgpu_mmap_fault(struct vm_fault *vmf)
{
	vm_fault_t ret;
	struct vm_area_struct *vma = vmf->vma;
	struct vfio_pci_region *region = vma->vm_private_data;
	struct vfio_pci_nvgpu_data *data = region->data;
	unsigned long vmf_off = (vmf->address - vma->vm_start) >> PAGE_SHIFT;
	unsigned long nv2pg = data->gpu_hpa >> PAGE_SHIFT;
	unsigned long vm_pgoff = vma->vm_pgoff &
		((1U << (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	unsigned long pfn = nv2pg + vm_pgoff + vmf_off;

	ret = vmf_insert_pfn(vma, vmf->address, pfn);
	trace_vfio_pci_nvgpu_mmap_fault(data->gpdev, pfn << PAGE_SHIFT,
			vmf->address, ret);

	return ret;
}