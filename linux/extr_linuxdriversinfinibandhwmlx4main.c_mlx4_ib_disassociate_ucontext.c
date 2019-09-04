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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_start; } ;
struct mlx4_ib_ucontext {TYPE_1__* hw_bar_info; } ;
struct ib_ucontext {int dummy; } ;
struct TYPE_2__ {struct vm_area_struct* vma; } ;

/* Variables and functions */
 int HW_BAR_COUNT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_MAYSHARE ; 
 int VM_SHARED ; 
 struct mlx4_ib_ucontext* to_mucontext (struct ib_ucontext*) ; 
 int /*<<< orphan*/  zap_vma_ptes (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_ib_disassociate_ucontext(struct ib_ucontext *ibcontext)
{
	int i;
	struct vm_area_struct *vma;
	struct mlx4_ib_ucontext *context = to_mucontext(ibcontext);

	/* need to protect from a race on closing the vma as part of
	 * mlx4_ib_vma_close().
	 */
	for (i = 0; i < HW_BAR_COUNT; i++) {
		vma = context->hw_bar_info[i].vma;
		if (!vma)
			continue;

		zap_vma_ptes(context->hw_bar_info[i].vma,
			     context->hw_bar_info[i].vma->vm_start, PAGE_SIZE);

		context->hw_bar_info[i].vma->vm_flags &=
			~(VM_SHARED | VM_MAYSHARE);
		/* context going to be destroyed, should not access ops any more */
		context->hw_bar_info[i].vma->vm_ops = NULL;
	}
}