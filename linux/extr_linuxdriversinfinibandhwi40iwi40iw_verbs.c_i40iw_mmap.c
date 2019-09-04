#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct vm_area_struct {int vm_pgoff; void* vm_page_prot; int /*<<< orphan*/  vm_start; struct i40iw_ucontext* vm_private_data; } ;
struct ib_ucontext {int dummy; } ;
struct i40iw_ucontext {TYPE_3__* iwdev; } ;
struct TYPE_4__ {scalar_t__ is_pf; } ;
struct TYPE_6__ {TYPE_2__* ldev; TYPE_1__ sc_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I40IW_DB_ADDR_OFFSET ; 
 int I40IW_PF_FIRST_PUSH_PAGE_INDEX ; 
 int I40IW_PUSH_OFFSET ; 
 int I40IW_VF_DB_ADDR_OFFSET ; 
 int I40IW_VF_FIRST_PUSH_PAGE_INDEX ; 
 int I40IW_VF_PUSH_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pgprot_noncached (void*) ; 
 void* pgprot_writecombine (void*) ; 
 struct i40iw_ucontext* to_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int i40iw_mmap(struct ib_ucontext *context, struct vm_area_struct *vma)
{
	struct i40iw_ucontext *ucontext;
	u64 db_addr_offset;
	u64 push_offset;

	ucontext = to_ucontext(context);
	if (ucontext->iwdev->sc_dev.is_pf) {
		db_addr_offset = I40IW_DB_ADDR_OFFSET;
		push_offset = I40IW_PUSH_OFFSET;
		if (vma->vm_pgoff)
			vma->vm_pgoff += I40IW_PF_FIRST_PUSH_PAGE_INDEX - 1;
	} else {
		db_addr_offset = I40IW_VF_DB_ADDR_OFFSET;
		push_offset = I40IW_VF_PUSH_OFFSET;
		if (vma->vm_pgoff)
			vma->vm_pgoff += I40IW_VF_FIRST_PUSH_PAGE_INDEX - 1;
	}

	vma->vm_pgoff += db_addr_offset >> PAGE_SHIFT;

	if (vma->vm_pgoff == (db_addr_offset >> PAGE_SHIFT)) {
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		vma->vm_private_data = ucontext;
	} else {
		if ((vma->vm_pgoff - (push_offset >> PAGE_SHIFT)) % 2)
			vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		else
			vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}

	if (io_remap_pfn_range(vma, vma->vm_start,
			       vma->vm_pgoff + (pci_resource_start(ucontext->iwdev->ldev->pcidev, 0) >> PAGE_SHIFT),
			       PAGE_SIZE, vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}