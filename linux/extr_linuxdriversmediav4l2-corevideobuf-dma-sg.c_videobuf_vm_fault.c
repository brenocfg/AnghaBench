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
struct vm_fault {struct page* page; int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_USER ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int __GFP_DMA32 ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  clear_user_highpage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t videobuf_vm_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct page *page;

	dprintk(3, "fault: fault @ %08lx [vma %08lx-%08lx]\n",
		vmf->address, vma->vm_start, vma->vm_end);

	page = alloc_page(GFP_USER | __GFP_DMA32);
	if (!page)
		return VM_FAULT_OOM;
	clear_user_highpage(page, vmf->address);
	vmf->page = page;

	return 0;
}