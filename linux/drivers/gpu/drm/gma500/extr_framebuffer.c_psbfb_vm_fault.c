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
typedef  int vm_fault_t ;
struct vm_fault {unsigned long address; unsigned long pgoff; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; struct psb_framebuffer* vm_private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * obj; struct drm_device* dev; } ;
struct psb_framebuffer {TYPE_1__ base; } ;
struct gtt_range {unsigned long offset; } ;
struct drm_psb_private {scalar_t__ stolen_base; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PFN_DEV ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  __pfn_to_pfn_t (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 struct gtt_range* to_gtt_range (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int vma_pages (struct vm_area_struct*) ; 
 int vmf_insert_mixed (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t psbfb_vm_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct psb_framebuffer *psbfb = vma->vm_private_data;
	struct drm_device *dev = psbfb->base.dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gtt_range *gtt = to_gtt_range(psbfb->base.obj[0]);
	int page_num;
	int i;
	unsigned long address;
	vm_fault_t ret = VM_FAULT_SIGBUS;
	unsigned long pfn;
	unsigned long phys_addr = (unsigned long)dev_priv->stolen_base +
				  gtt->offset;

	page_num = vma_pages(vma);
	address = vmf->address - (vmf->pgoff << PAGE_SHIFT);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	for (i = 0; i < page_num; i++) {
		pfn = (phys_addr >> PAGE_SHIFT);

		ret = vmf_insert_mixed(vma, address,
				__pfn_to_pfn_t(pfn, PFN_DEV));
		if (unlikely(ret & VM_FAULT_ERROR))
			break;
		address += PAGE_SIZE;
		phys_addr += PAGE_SIZE;
	}
	return ret;
}