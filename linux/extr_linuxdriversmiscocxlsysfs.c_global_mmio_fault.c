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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long pgoff; int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {struct ocxl_afu* vm_private_data; } ;
struct TYPE_2__ {unsigned long global_mmio_size; } ;
struct ocxl_afu {unsigned long global_mmio_start; TYPE_1__ config; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  vmf_insert_pfn (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static vm_fault_t global_mmio_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct ocxl_afu *afu = vma->vm_private_data;
	unsigned long offset;

	if (vmf->pgoff >= (afu->config.global_mmio_size >> PAGE_SHIFT))
		return VM_FAULT_SIGBUS;

	offset = vmf->pgoff;
	offset += (afu->global_mmio_start >> PAGE_SHIFT);
	return vmf_insert_pfn(vma, vmf->address, offset);
}