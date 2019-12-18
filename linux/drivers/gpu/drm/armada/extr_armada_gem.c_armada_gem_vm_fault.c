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
struct vm_fault {unsigned long address; TYPE_1__* vma; } ;
struct drm_gem_object {int dummy; } ;
struct armada_gem_object {unsigned long phys_addr; } ;
struct TYPE_2__ {unsigned long vm_start; struct drm_gem_object* vm_private_data; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct armada_gem_object* drm_to_armada_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_insert_pfn (TYPE_1__*,unsigned long,unsigned long) ; 

__attribute__((used)) static vm_fault_t armada_gem_vm_fault(struct vm_fault *vmf)
{
	struct drm_gem_object *gobj = vmf->vma->vm_private_data;
	struct armada_gem_object *obj = drm_to_armada_gem(gobj);
	unsigned long pfn = obj->phys_addr >> PAGE_SHIFT;

	pfn += (vmf->address - vmf->vma->vm_start) >> PAGE_SHIFT;
	return vmf_insert_pfn(vmf->vma, vmf->address, pfn);
}