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
struct vm_fault {int pgoff; int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {struct drm_gem_object* vm_private_data; } ;
struct page {int dummy; } ;
struct drm_gem_shmem_object {struct page** pages; } ;
struct drm_gem_object {int size; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_insert_page (struct vm_area_struct*,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static vm_fault_t drm_gem_shmem_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_gem_object *obj = vma->vm_private_data;
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	loff_t num_pages = obj->size >> PAGE_SHIFT;
	struct page *page;

	if (vmf->pgoff >= num_pages || WARN_ON_ONCE(!shmem->pages))
		return VM_FAULT_SIGBUS;

	page = shmem->pages[vmf->pgoff];

	return vmf_insert_page(vma, vmf->address, page);
}