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
struct vm_area_struct {int vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct hns_roce_dev {int tptr_dma_addr; int /*<<< orphan*/  tptr_size; } ;
struct TYPE_3__ {int pfn; } ;
struct TYPE_4__ {TYPE_1__ uar; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int rdma_user_mmap_io (struct ib_ucontext*,struct vm_area_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_hr_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int hns_roce_mmap(struct ib_ucontext *context,
			 struct vm_area_struct *vma)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(context->device);

	switch (vma->vm_pgoff) {
	case 0:
		return rdma_user_mmap_io(context, vma,
					 to_hr_ucontext(context)->uar.pfn,
					 PAGE_SIZE,
					 pgprot_noncached(vma->vm_page_prot));

	/* vm_pgoff: 1 -- TPTR */
	case 1:
		if (!hr_dev->tptr_dma_addr || !hr_dev->tptr_size)
			return -EINVAL;
		/*
		 * FIXME: using io_remap_pfn_range on the dma address returned
		 * by dma_alloc_coherent is totally wrong.
		 */
		return rdma_user_mmap_io(context, vma,
					 hr_dev->tptr_dma_addr >> PAGE_SHIFT,
					 hr_dev->tptr_size,
					 vma->vm_page_prot);

	default:
		return -EINVAL;
	}
}