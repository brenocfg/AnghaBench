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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long address; struct page* page; struct vm_area_struct* vma; } ;
struct vm_area_struct {unsigned long vm_start; TYPE_2__* vm_file; } ;
struct page {int dummy; } ;
struct drm_file {TYPE_1__* minor; } ;
struct drm_device_dma {scalar_t__* pagelist; } ;
struct drm_device {struct drm_device_dma* dma; } ;
struct TYPE_4__ {struct drm_file* private_data; } ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned long,unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static vm_fault_t drm_vm_dma_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_file *priv = vma->vm_file->private_data;
	struct drm_device *dev = priv->minor->dev;
	struct drm_device_dma *dma = dev->dma;
	unsigned long offset;
	unsigned long page_nr;
	struct page *page;

	if (!dma)
		return VM_FAULT_SIGBUS;	/* Error */
	if (!dma->pagelist)
		return VM_FAULT_SIGBUS;	/* Nothing allocated */

	offset = vmf->address - vma->vm_start;
					/* vm_[pg]off[set] should be 0 */
	page_nr = offset >> PAGE_SHIFT; /* page_nr could just be vmf->pgoff */
	page = virt_to_page((void *)dma->pagelist[page_nr]);

	get_page(page);
	vmf->page = page;

	DRM_DEBUG("dma_fault 0x%lx (page %lu)\n", offset, page_nr);
	return 0;
}