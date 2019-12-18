#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  pgoff; TYPE_3__* page; TYPE_2__* vma; } ;
struct msc_iter {struct msc* msc; } ;
struct msc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; int /*<<< orphan*/  mapping; } ;
struct TYPE_6__ {TYPE_1__* vm_file; } ;
struct TYPE_5__ {int /*<<< orphan*/  f_mapping; struct msc_iter* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (TYPE_3__*) ; 
 TYPE_3__* msc_buffer_get_page (struct msc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t msc_mmap_fault(struct vm_fault *vmf)
{
	struct msc_iter *iter = vmf->vma->vm_file->private_data;
	struct msc *msc = iter->msc;

	vmf->page = msc_buffer_get_page(msc, vmf->pgoff);
	if (!vmf->page)
		return VM_FAULT_SIGBUS;

	get_page(vmf->page);
	vmf->page->mapping = vmf->vma->vm_file->f_mapping;
	vmf->page->index = vmf->pgoff;

	return 0;
}