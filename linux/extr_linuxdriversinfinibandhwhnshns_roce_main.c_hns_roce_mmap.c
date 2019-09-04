#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_end; int vm_start; int vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct hns_roce_dev {int tptr_dma_addr; int tptr_size; } ;
struct TYPE_4__ {int pfn; } ;
struct TYPE_5__ {TYPE_1__ uar; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int hns_roce_set_vma_data (struct vm_area_struct*,TYPE_2__*) ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_hr_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int hns_roce_mmap(struct ib_ucontext *context,
			 struct vm_area_struct *vma)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(context->device);

	if (((vma->vm_end - vma->vm_start) % PAGE_SIZE) != 0)
		return -EINVAL;

	if (vma->vm_pgoff == 0) {
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		if (io_remap_pfn_range(vma, vma->vm_start,
				       to_hr_ucontext(context)->uar.pfn,
				       PAGE_SIZE, vma->vm_page_prot))
			return -EAGAIN;
	} else if (vma->vm_pgoff == 1 && hr_dev->tptr_dma_addr &&
		   hr_dev->tptr_size) {
		/* vm_pgoff: 1 -- TPTR */
		if (io_remap_pfn_range(vma, vma->vm_start,
				       hr_dev->tptr_dma_addr >> PAGE_SHIFT,
				       hr_dev->tptr_size,
				       vma->vm_page_prot))
			return -EAGAIN;
	} else
		return -EINVAL;

	return hns_roce_set_vma_data(vma, to_hr_ucontext(context));
}